#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    uint16_t server_port = 3000;
    struct sockaddr_in sin;
    ssize_t sent_bytes, read_bytes;
    char buffer[4096], data[4096] = "Hello Server";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(server_port);
    
    while(sock < 0)
    {
        perror("sokcet failed");
        sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    while(connect(sock, &sin, sizeof(sin)) < 0) 
    {
        perror("connection failed");
        connect(sock, &sin, sizeof(sin));
    }
    
    sent_bytes = send(sock, data, sizeof(data), 0);

    if(sent_bytes < 0)
    {
        perror("send failed");
    }

    read_bytes = recv(sock, buffer, sizeof(buffer), 0);
    if(read_bytes < 0)
    {
        perror("recv failed");
    }
    else
    {
        printf("%s\n", buffer);
    }

    close(sock);
    return 0;
}
