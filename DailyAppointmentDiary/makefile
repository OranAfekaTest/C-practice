# makefile sample

TARGET= AD.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= AD.o ADMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
AD.o: AD.c AD.h
	$(CC) $(CFLAGS) -c AD.c
	
ADMain.o: ADMain.c AD.h
	$(CC) $(CFLAGS) -c ADMain.c
	
clean:
	rm -f $(TARGET) $(OBJS)
