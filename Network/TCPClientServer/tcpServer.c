#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "../../Generics/List/listFunctions.h"
#define TRUE 1
#define FAIL -1
#define ACTION_FAILED 0

static void NoBlocking(int _socket);
static int ServerInit(int* _listeningSock, int _optval, struct sockaddr_in* _sin, int _port, int _backLog, List** _clients);
static int CheckNewClients(int _listeningSock, int optval, List* _clients);
static int CheckCurClients(List* _clients);
static int CheckClientAction(void* _clientSock, void* _context);
static int DestroyServer(int _listeningSock, List* _clients);
static void CloseClient(void* _clientSock);

int main(void)
{
    uint16_t server_port = 3000;
    struct sockaddr_in sin;
    List* clients = NULL;
    int listening_sock;
    int optval = 1;
    int back_log = 32;
    
    if(FAIL == ServerInit(&listening_sock, optval, &sin, server_port, back_log, &clients))/*socket, setsocketopt, bind, listen*/
    {
        puts("Failed to initialize server");
    }
    else
    {
        while(TRUE)
        {
            CheckNewClients(listening_sock, optval, clients);/*accept*/
            CheckCurClients(clients);/*recv, send*/
        }
    }
    

    DestroyServer(listening_sock, clients);/*close*/

    return 0;
}

void NoBlocking(int _socket)
{
    int flags;
    if(FAIL == (flags = fcntl(_socket, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return;
    }

    if(FAIL == fcntl(_socket, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
        return;
    }
}

int ServerInit(int* _listeningSock, int _optval, struct sockaddr_in* _sin, int _port, int _backLog, List** _clients)
{
    *_listeningSock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(setsockopt(*_listeningSock, SOL_SOCKET, SO_REUSEADDR, &_optval, sizeof(_optval)) < 0) 
    {
        perror("reuse failed");
        return FAIL;
    }

    if(*_listeningSock < 0)
    {
        perror("sokcet failed");
        return FAIL;
    }
    NoBlocking(*_listeningSock);

    memset(_sin, 0, sizeof(*_sin));
    _sin->sin_family = AF_INET;
    _sin->sin_addr.s_addr = INADDR_ANY;
    _sin->sin_port = htons(_port);
    

    if(bind(*_listeningSock, (struct sockaddr*)_sin, sizeof(*_sin)) < 0)
    {
        perror("bind failed");
        return FAIL;
    }

    if(listen(*_listeningSock, _backLog) < 0)
    {
        perror("listen failed");
        return FAIL;
    }

    *_clients = ListCreate();
    if(!*_clients)
    {
        puts("Failed to create client list");
        return FAIL;
    }
    return TRUE;
}

int CheckNewClients(int _listeningSock, int optval, List* _clients)
{
    struct sockaddr_in client_sin;
    socklen_t addr_len = sizeof(client_sin);
    int* client_sock = malloc(sizeof(int));
    *client_sock = accept(_listeningSock, (struct sockaddr *)&client_sin, &addr_len);
    if(!_clients)
    {
        puts("NULL client List on Check New Clients");
        free(client_sock);
        return FAIL;
    }
    /*
    if(setsockopt(*client_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) 
    {
        perror("reuse failed");
        free(client_sock);
        return FAIL;
    }
    */
    if(*client_sock < 0  && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        perror("“accept failed”");
        free(client_sock);
        return FAIL;
    }
    else if(0 < *client_sock)
    {
        NoBlocking(*client_sock);
        printf("pushing client socket %d to list\n", *client_sock);
        ListPushHead(_clients, (void*)client_sock);
    }
    
    return TRUE;
}

int CheckCurClients(List* _clients)
{
    ListItr begin = NULL, end = NULL, check = NULL;
    if(!_clients)
    {
        puts("NULL client List on Check Current Clients");
        return FAIL;
    }
    begin = ListItrBegin(_clients);
    end = ListItrEnd(_clients);
    if(!begin || !end)
    {
        puts("NULL List iterators");
        return FAIL;
    }
    if(begin != end)
    {
        check = ListItrForEach(begin, end, CheckClientAction, NULL);
        if(end != check)
        {
            ListItrRemove(check);
            return ACTION_FAILED;
        }
    }
    
    return TRUE;
}

int CheckClientAction(void* _clientSock, void* _context)
{
    char buffer[4096], data[4096] = "Hello Client";
    ssize_t sent_bytes, read_bytes;

    read_bytes = recv(*((int*)_clientSock), buffer, sizeof(buffer), 0);
    if(read_bytes == 0 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        printf("received no data from client on socket %d\n", *(int*)_clientSock);
        return ACTION_FAILED;
    }
    else if(read_bytes < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        perror("recv failed");
        /*close(*((int*)_clientSock));*/
        return FAIL;
    }
    else if(0 < read_bytes)
    {
        /*puts(buffer);*/
        printf("%s bytes read:%ld\n", buffer, read_bytes);
        sent_bytes = send(*(int*)_clientSock, data, sizeof(data), 0);
        if(sent_bytes < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
            perror("send failed");
            return ACTION_FAILED;
        }
    }
    
    
    return TRUE;
}

int DestroyServer(int _listeningSock, List* _clients)
{
    puts("Destroyinf server");
    if(_clients)
    {
        ListDestroy(&_clients, CloseClient);
    }
    close(_listeningSock);
    return TRUE;
}

void CloseClient(void* _clientSock)
{
    close(*((int*)_clientSock));
    free(_clientSock);
}