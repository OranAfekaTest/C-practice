#include "serverNet.h"
#include "../../Generics/List/listFunctions.h"
#include <errno.h>
#include "ADTUtils.h"

#define FD_MAX 1023
#define OPTVAL 1
#define SUCCES 1
#define ACTION_FAILED 0
#define STOP 1

struct Server
{
    int m_listeninSocket;
    uint16_t m_port;
    struct sockaddr_in m_sin;
    List* m_clients;
    fd_set m_masterFDs;
    fd_set m_readFDs;
    fpNewMessage m_fpNewMessage;
    fpNewClient m_fpNewClient;
    fpCloseClient m_fpCloseClient;
    fpFail m_fpFail;
    void* m_context;
    int m_flag;
};

static int SocketInit(struct sockaddr_in *_sin , int _optval, uint16_t _port);
static int CheckNewClients(Server* _server);
static int CheckCurClients(Server* _server);
static int CheckClientAction(void* _clientSock, void* _context);
static void EndConnection(Server* _server, ListItr _client);
static void SocketDestroy(void* _element);

Server* CreateServerNet(uint16_t _serverPort , fpNewMessage _fpNewMessage , fpNewClient _fpNewClient , fpCloseClient _fpCloseClient , fpFail _fpFail, void* _context)
{
    Server* server = NULL;
    if(!_fpNewMessage)
    {
        puts("NULL NewMessage function pointer at CreateServerNet");
        /*puts("NULL argument at CreateServerNet");*/
        return NULL;
    }
    server = malloc(sizeof(Server));
    if(!server)
    {
        return server;
    }
    
    server->m_flag = 0;
    server->m_port = _serverPort;

    if(FAIL == (server->m_listeninSocket = SocketInit(&server->m_sin, OPTVAL, server->m_port)))
    {
        free(server);
        return NULL;
    }

    server->m_clients = ListCreate();
    if(!server->m_clients)
    {
        free(server);
        return NULL;
    }

    server->m_fpNewMessage = _fpNewMessage;
    server->m_fpNewClient = _fpNewClient;
    server->m_fpCloseClient = _fpCloseClient;
    server->m_fpFail = _fpFail;
    server->m_context = _context;

    FD_ZERO(&server->m_masterFDs);
    FD_ZERO(&server->m_readFDs);
    FD_SET(server->m_listeninSocket, &server->m_masterFDs);

    return server;
}

void RunServerNet(Server* _server)
{
    int activity, status;
    if(!_server)
    {
        puts("NULL server pointer at RunServerNet");
        return;
    }
    
    while(!_server->m_flag)
    {
        _server->m_readFDs = _server->m_masterFDs;
        activity = select(FD_MAX + 1, &_server->m_readFDs, NULL, NULL, NULL);
        if(activity < 0 && errno != EINTR)
        {
            perror("select failed");
            if(_server->m_fpFail)
            {
                _server->m_fpFail(_server, activity, "select failed", NULL);
            }
            return;
        }

        if(0 < activity)
        {
            status = CheckCurClients(_server);
            if(_server->m_fpFail && status == FAIL)
            {
                _server->m_fpFail(_server, activity, "CheckCurClients failed", NULL);
            }
            if(FD_ISSET(_server->m_listeninSocket, &_server->m_readFDs))
            {
                status = CheckNewClients(_server);
                if(_server->m_fpFail && status == FAIL)
                {
                    _server->m_fpFail(_server, activity, "CheckNewClients failed", NULL);
                }
            }
        }
    }
}

void DestroyServerNet(Server** _server)
{
    if(*_server)
    {
        close((*_server)->m_listeninSocket);
        ListDestroy(&(*_server)->m_clients, SocketDestroy);
        free(*_server);
        *_server = NULL;
    }
}

void StopServerNet(Server* _server)
{
    if(_server)
    {
        _server->m_flag = STOP;
    }
}

int SendMessage(Server* _server, int _clientSocket, void* _buffer, size_t _msgSize)
{
    ssize_t sent_bytes;
    if(!_server || _clientSocket < 0 || !_buffer || !_msgSize)
    {
        return FAIL;
    }
    sent_bytes = send(_clientSocket, _buffer, _msgSize, 0);
    if(sent_bytes < 0)
    {
        perror("send failed");
        if(_server->m_fpFail)
        {
            _server->m_fpFail(_server, _clientSocket, "send failed", _buffer);
        }
        return FAIL;
    }
    return sent_bytes;
}

int SocketInit(struct sockaddr_in *_sin ,int _optval, uint16_t _port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &_optval, sizeof(_optval)) < 0) 
    {
        perror("reuse failed");
        return FAIL;
    }

    if(sock < 0)
    {
        perror("sokcet failed");
        return FAIL;
    }

    memset(_sin, 0, sizeof(*_sin));
    _sin->sin_family = AF_INET;
    _sin->sin_addr.s_addr = INADDR_ANY;
    _sin->sin_port = htons(_port);
    

    if(bind(sock, (struct sockaddr*)_sin, sizeof(*_sin)) < 0)
    {
        perror("bind failed");
        return FAIL;
    }    
    
    if(listen(sock, BACK_LOG) < 0)
    {
        perror("listen failed");
        return FAIL;
    }

    return sock;
}

int CheckNewClients(Server* _server)
{
    struct sockaddr_in client_sin;
    socklen_t addr_len = sizeof(client_sin);
    int client_sock, *pSocket = NULL;

    client_sock = accept(_server->m_listeninSocket, (struct sockaddr *)&client_sin, &addr_len);
    
    if(BACK_LOG <= ListSize(_server->m_clients))
    {
        puts("server is full");
        return FAIL;
    }

    if(client_sock < 0)
    {
        perror("accept failed");
        return FAIL;
    }
    else if(0 < client_sock)
    {
        pSocket = (int*)malloc(sizeof(int));
        if(pSocket)
        {
            printf("pushing client socket %d to list\n", client_sock);
            *pSocket = client_sock;
            ListPushHead(_server->m_clients, (void*)pSocket);
            FD_SET(client_sock, &_server -> m_masterFDs);
        }
    }
    
    return SUCCES;
}

int CheckCurClients(Server* _server)
{
    ListItr begin = NULL, end = NULL, check = NULL;
    begin = ListItrBegin(_server->m_clients);
    end = ListItrEnd(_server->m_clients);
    
    if(!begin || !end)
    {
        puts("NULL List iterators");
        return FAIL;
    }

    if(begin != end)
    {
        check = ListItrForEach(begin, end, CheckClientAction, (void*)_server);
        if(_server->m_flag)
        {
            return;
        }
        if(end != check)
        {
            EndConnection(_server, check);
            return FAIL;
        }
    }
    
    return SUCCES;
}

int CheckClientAction(void* _clientSock, void* _context)
{
    Server* server = (Server*)_context;
    int sock = *(int*)_clientSock;
    char buffer[BUFFER_SIZE];
    ssize_t read_bytes;

    if(FD_ISSET(sock, &server->m_readFDs))
    {
        read_bytes = recv(sock, buffer, sizeof(buffer), 0);
        if(read_bytes == 0)
        {
            printf("received no data from client on socket %d\n", sock);
            return ACTION_FAILED;
        }
        else if(read_bytes < 0)
        {
            perror("recv failed");
            return ACTION_FAILED;
        }
        else
        {
            server->m_fpNewMessage(server, sock, buffer, read_bytes, server->m_context);
        }
    }

    return SUCCES;
}

void EndConnection(Server* _server, ListItr _client)
{
    int* removedSocket = (int*)ListItrRemove(_client);
    printf("error on socket %d, disconnecting from client.\n", *removedSocket);
    if(_server->m_fpCloseClient)
    {
        _server->m_fpCloseClient(*removedSocket);
    }
    FD_CLR(*removedSocket, &_server->m_masterFDs);
    close(*removedSocket);
    free(removedSocket);
}

void SocketDestroy(void* _element)
{
    int* socket = (int*)_element;
    close(*socket);
    free(socket);
}