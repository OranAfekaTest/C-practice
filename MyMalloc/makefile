# My Malloc makefile

TARGET= myMalloc.out
CC= gcc
CFLAGS= -ansi -g -pedantic -lm
OBJS= myMalloc.o myMallocTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
myMalloc.o: myMalloc.c myMalloc.h
	$(CC) $(CFLAGS) -c myMalloc.c

myMallocTest.o: myMallocTest.c myMalloc.h
	$(CC) $(CFLAGS) -c myMallocTest.c

clean:
	rm -f $(TARGET) $(OBJS)