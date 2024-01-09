# genList makefile

TARGET= genList.out
CC= gcc

CFLAGS= -ansi -g -pedantic
OBJS= genList.o listItr.o listFunctions.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genList.o: genList.c genList.h listInternal.h
	$(CC) $(CFLAGS) -c genList.c

listItr.o: listItr.c listItr.h listInternal.h
	$(CC) $(CFLAGS) -c listItr.c

listFunctions.o: listFunctions.c listFunctions.h listItr.h
	$(CC) $(CFLAGS) -c listFunctions.c
	
clean:
	rm -f $(TARGET) $(OBJS)
