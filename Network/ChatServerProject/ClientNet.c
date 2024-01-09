#include "ClientNet.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>



struct ClientNet
{
    int m_sockClient;
};


/***********************/
ClientNet* createClient()
{
	ClientNet* clientNet = NULL ; 
	int sock;
	struct sockaddr_in _sin;
	clientNet = (ClientNet*)malloc(sizeof(ClientNet));
	if(!clientNet)
	{
		return NULL;
	}
	sock = ClientInitialization();
	if(sock<0)
	{
		perror("Socket fail!\n");
		free(clientNet);
		return NULL;
	}
	
	clientNet-> m_sockClient = sock;
	return clientNet;
}

int ClientInitialization()
{
	int optval = 1;
	struct sockaddr_in _sin;
	int sock = socket(AF_INET,SOCK_STREAM,0);
	memset (&_sin, 0, sizeof(_sin)); /*Reset the struct	*/
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = inet_addr(SERVER_IP);
    _sin.sin_port = htons(SERVER_PORT);
    
    if (connect(sock, (struct sockaddr*)&_sin, sizeof(_sin)) < 0)
	{	
		perror("Connect fail!\n");
		return CONNECT_SOCKEOPT_FAIL;	
	}
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		perror("Setsockopt fail!\n");
		return SET_SOCKEOPT_FAIL;
	}	

	return sock;
}



ssize_t Send(ClientNet* _client ,  char* _buffer, int _length)
{
	ssize_t bytesSent ;
    bytesSent = send(_client->m_sockClient, _buffer, _length, 0);
    if (bytesSent == FAIL)
    {
        perror("Send failed");
        return FAIL;
    }
	return bytesSent;
}

ssize_t Receive(ClientNet* _client ,  char* _buffer, int _length)
{
	ssize_t bytesReceived ;
	bytesReceived = recv(_client->m_sockClient, _buffer, _length, 0);
    if (bytesReceived == FAIL)
    {
        perror("Receive failed");
        return FAIL;
    }
	return bytesReceived;
}

void ClientNetDestroy(ClientNet* clientNet)
{
    if (clientNet != NULL)
    {
        close(clientNet->m_sockClient);
        free(clientNet);
    }
}

















/**********************************************************/

/*
void testCreateClient()
{
    ClientNet* client = createClient();
    if (client != NULL)
    {
        printf("createClient: Passed\n");
    }
    else
    {
        printf("createClient: Failed\n");
    }
}

void testClientInitialization()
{
    struct sockaddr_in sin;
    int socket_fd = ClientInitialization(&sin);
    if (socket_fd >= 0)
    {
        printf("ClientInitialization: Passed\n");
    }
    else
    {
        printf("ClientInitialization: Failed\n");
    }
}

void testRunClientNet()
{
    ClientNet* client = createClient();
    if (client != NULL)
    {
        char buffer[256] = "Hello, Server!";
        int length = strlen(buffer);
        RunClientNet(client, buffer, length);
        printf("RunClientNet: Passed\n");
    }
    else
    {
        printf("RunClientNet: Failed (Failed to create client)\n");
    }
}

void testSendReceive()
{
    ClientNet* client = createClient();
    if (client != NULL)
    {
        char buffer[256] = "Hello, Server!";
        int length = strlen(buffer);
        SendRecive(client, buffer, length);
        printf("SendReceive: Passed\n");
    }
    else
    {
        printf("SendReceive: Failed (Failed to create client)\n");
    }
}

int main()
{
    testCreateClient();
    testClientInitialization();
    testRunClientNet();
    testSendReceive();

    return 0;
}

*/









