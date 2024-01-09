# genBST makefile

TARGET= genBST.out
CC= gcc
CFLAGS= -ansi -g -pedantic -lt
OBJS= genBST.o genBSTtest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genBST.o: genBST.c genBST.h
	$(CC) $(CFLAGS) -c genBST.c
	
genBSTTest.o: genBSTTest.c genBST.h
	$(CC) $(CFLAGS) -c genBSTTest.c
	
clean:
	rm -f $(TARGET) $(OBJS)