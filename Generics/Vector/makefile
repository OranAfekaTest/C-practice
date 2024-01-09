# makefile sample

TARGET= genVector.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= genVector.o genVectorMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
genVector.o: genVector.c genVector.h
	$(CC) $(CFLAGS) -c genVector.c
	
genVectorMain.o: genVectorMain.c genVector.h
	$(CC) $(CFLAGS) -c genVectorMain.c
	
clean:
	rm -f $(TARGET) $(OBJS)
