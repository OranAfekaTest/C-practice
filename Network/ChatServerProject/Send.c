#include <netinet/in.h>
#include <sys/types.h> /* pid_t */
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define MAX_MASSAGE_SIZE 1000
#define LOCAL_INTERFACE "127.0.0.1"
#define TRUE 1


static void InnerProtocolPack( char* _message, char* _name );


int main (int argc, char* argv[])
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	char pidStr[20];
	pid_t pid;
	FILE* fp;
	if(sock < 0 )
	{
		perror("Socket Failed");
		return -1;
	}
	fp = fopen("SendPID.txt", "w" );
	if( fp == NULL )
	{
		perror("Error opening file");
		close( sock );
		return -1;
	}
	pid = getppid();
	sprintf( pidStr, "%d", pid);
	if( fputs( pidStr, fp ) == EOF )
	{
		perror("Error writing to file");
		close( sock );
		return -1;
	}
	fclose( fp );
	if( !SendTo( sock, argc, argv ) )
	{
		close( sock );
		return -1;
	}
}

int SendTo(int _sock, int _argc, char* _argv[])
{
	ssize_t sent_bytes;
	char message[MAX_MASSAGE_SIZE], loopch = 0;
	struct sockaddr_in sin;
	struct in_addr localInt;
	memset( &sin, 0, sizeof( sin ) );
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr( _argv[1] );
	sin.sin_port = htons( atoi(_argv[2]) );
	while (TRUE)
	{
		memset( message, 0, MAX_MASSAGE_SIZE);
		fgets( message, MAX_MASSAGE_SIZE, stdin );
		InnerProtocolPack( message, _argv[3] );
		sent_bytes = sendto( _sock, message, MAX_MASSAGE_SIZE, 0, (struct sockaddr *) &sin, sizeof(sin) );
		if( sent_bytes < 0 )
		{
			perror("sendto failed");
			return 0;
		}
	}
}

static void InnerProtocolPack( char* _message, char* _name )
{
	strcat( _message, _name );
}
	
	
	
	
	
