# TCP Client Server makefile 

TARGET= server.out
CC= gcc
CFLAGS= -ansi -g -pedantic -L/home/user/h74/Generics -lGenerics
OBJS= TCPServer.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

TCPServer.o: tcpServer.c
	$(CC) $(CFLAGS) -c tcpServer.c

clean:
	rm -f $(TARGET) $(OBJS)