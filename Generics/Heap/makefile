# genHeap makefile

TARGET= genHeap.out
CC= gcc
VECTORPATH= ../Vector/
CFLAGS= -ansi -g -pedantic
OBJS= genHeap.o genHeapTests.o genVector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genVector.o: $(VECTORPATH)genVector.c $(VECTORPATH)genVector.h
	$(CC) $(CFLAGS) -c $(VECTORPATH)genVector.c	

genHeap.o: genHeap.c genHeap.h $(VECTORPATH)genVector.h
	$(CC) $(CFLAGS) -c genHeap.c
	
genHeapTests.o: genHeapTests.c genHeap.h $(VECTORPATH)genVector.h
	$(CC) $(CFLAGS) -c genHeapTests.c
	
clean:
	rm -f $(TARGET) $(OBJS)