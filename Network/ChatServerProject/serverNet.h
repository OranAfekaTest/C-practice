#ifndef __SERVERNET__H__ 
#define __SERVERNET__H__ 
#include <sys/select.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <netinet/in.h> 
#include <stdlib.h> 

typedef struct Server Server; 
typedef int (*fpNewMessage)(Server* _server, int _clientSocket , void* _buffer , size_t _msgSize , void* _context); 
typedef int (*fpNewClient)(int _clientSocket); 
typedef int (*fpCloseClient)(int _clientSocket); 
typedef	void (*fpFail)(Server* _server, int _clientSocket, void* message, void* context); 

Server* CreateServerNet(uint16_t _serverPort, fpNewMessage _fpNewMessage , fpNewClient _fpNewClient , fpCloseClient _fpCloseClient , fpFail _fpFail, void* _context); 
void RunServerNet(Server* _server); 
void DestroyServerNet(Server** _server);
void StopServerNet(Server* _server);
int SendMessage(Server* _server, int _clientSocket, void* _buffer, size_t _msgSize);

#endif

