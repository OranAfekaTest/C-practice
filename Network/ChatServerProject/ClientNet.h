#ifndef __CLIENT_NET_H__
#define __CLIENT_NET_H__

#include <sys/socket.h>
#include <netinet/in.h>
#define FAIL -1
#define SERVER_IP "3.239.199.222"
#define SERVER_PORT 3000
typedef struct ClientNet ClientNet;

typedef enum ClientResult
{
    CLIENT_SUCCESS,
    CLIENT_FAIL,
    CLIENT_NULL,
    SOCKET_FAIL,
    SET_SOCKEOPT_FAIL,
    CONNECT_SOCKEOPT_FAIL,
    CLIENT_ALLOCATION_FAIL
}ClientResult;


/*Description:
Creates a ClientNet object and initializes the client connection.
 *
 * Returns:
 *    - A pointer to the created ClientNet object on success.
 *    - NULL if an error occurred..*/
ClientNet* createClient();

/*Description:
Initializes the client socket and connects to the server.
 *
 * Returns:
 *    - The socket file descriptor on success.
 *    - -1 if an error occurred..*/
int ClientInitialization();
/*Description:
Destroys the ClientNet object and closes the client socket.
 *
 * Parameters:
 *    clientNet:   The ClientNet object to destroy.*/
void ClientNetDestroy(ClientNet* clientNet);
/*Description:
Sends data to the server.
 *
 * Parameters:
 *    _client:   The ClientNet object.
 *    _buffer:   A pointer to the buffer containing the data to send.
 *    _length:   The length of the data to send.
 *
 * Returns:
 *    - The number of bytes sent on success.
 *    - -1 if an error occurred.*/
ssize_t Send(ClientNet* _client ,  char* _buffer, int _length);
/*Description:
Receives data from the server.
 *
 * Parameters:
 *    _client:   The ClientNet object.
 *    _buffer:   A pointer to the buffer where received data will be stored.
 *    _length:   The length of the buffer.
 *
 * Returns:
 *    - The number of bytes received on success.
 *    - -1 if an error occurred.*/
ssize_t Receive(ClientNet* _client ,  char* _buffer, int _length);







#endif /*__CLIENT_NET_H__ */
