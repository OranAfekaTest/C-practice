#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    uint16_t server_port =3000;
    struct sockaddr_in sin;
    ssize_t sent_bytes;
    char data[4096] = "Hello Server";
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(server_port);
    
    while(sock < 0)
    {
        perror("sokcet failed");
        sock = socket(AF_INET, SOCK_DGRAM, 0);
    }

    sent_bytes = sendto(sock, data, sizeof(data), 0, &sin, sizeof(sin));

    while(sent_bytes < 0)
    {
        perror("bind failed");
        sent_bytes = sendto(sock, data, sizeof(data), 0, &sin, sizeof(sin));
    }

    close(sock);
    return 0;
}
