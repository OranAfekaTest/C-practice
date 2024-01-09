#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <netinet/in.h>
#include <sys/types.h> /* pid_t */
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define MAX_MASSAGE_SIZE 1000
#define LOCAL_INTERFACE "127.0.0.1"
#define TRUE 1

void InnerProtocolUnpack( char* _buffer );

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
	fp = fopen("ReceivePID.txt", "w" );
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
	fflush(stdout);
	fclose( fp );
	if( !RecvFrom( sock, argc, argv ) )
	{
		close( sock );
		return -1;
	}
}


int RecvFrom( int _sock, int _argc, char* _argv[])
{
	ssize_t read_bytes;
	int reuse = 1, port;
	char buffer[ MAX_MASSAGE_SIZE ];
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);
	struct ip_mreq group;
	memset( &sin, 0, sizeof( sin ) );
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr( _argv[1] );
	sin.sin_port = htons( atoi(_argv[2]) );
	if( setsockopt( _sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse) ) < 0)
	{
		perror("setting reuse failed");
		return 0;
	}
	if( bind( _sock, (struct sockaddr *) &sin, sizeof(sin) ) < 0 )
	{
		perror("bind failed");
		return 0;
	}
	group.imr_multiaddr.s_addr = inet_addr( _argv[1] );
	group.imr_interface.s_addr = INADDR_ANY;
	if( setsockopt( _sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group) ) < 0)
	{
		perror("adding multicast group failed");
		return 0;
	}
	while( TRUE )
	{
		read_bytes = read( _sock, buffer, sizeof(buffer) );
		if( read_bytes < 0 )
		{
			perror("read failed");
			return 0;
		}
		InnerProtocolUnpack( buffer );
		printf("%s\n",(char*)buffer);
		/*fflush(stdout);*/
	}
	return 1;
}


void InnerProtocolUnpack( char* _buffer )
{
	char temp[ MAX_MASSAGE_SIZE ], *message, *name;
	const char delim[2] = "\n";
	message = strtok( _buffer, delim);
	name = strtok( NULL, delim);
	strcat(name, ": ");
	strcpy( temp, name );
	strcat(temp, message);
	strcpy( _buffer, temp );
}
	
	




	
