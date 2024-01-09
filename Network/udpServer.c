#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    uint16_t server_port =3000;
    struct sockaddr_in sin;
    int read_bytes;
    int sin_len = sizeof(sin);
    char buffer[4096];
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    
    while(sock < 0)
    {
        perror("sokcet failed");
        sock = socket(AF_INET, SOCK_DGRAM, 0);
    }

    if(bind(sock, &sin, sin_len) < 0)
    {
        perror("bind failed");
    }

    read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, &sin, &sin_len);

    if(read_bytes < 0)
    {
        perror("recvfrom failed");
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, &sin, &sin_len);
    }

    printf("%s\n", buffer);

    close(sock);
    return 0;
}
