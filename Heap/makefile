# Heap makefile

PATH_VEC= ../DynamicVector/
TARGET= heap.out
CC= gcc
CFLAGS= -ansi -g -pedantic -lm
OBJS= heap.o heapMain.o ADTDef.o dynamicVector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

ADTDef.o: $(PATH_VEC)ADTDef.c $(PATH_VEC)ADTDef.h
	$(CC) $(CFLAGS) -c $(PATH_VEC)ADTDef.c

dynamicVector.o: $(PATH_VEC)dynamicVector.c $(PATH_VEC)dynamicVector.h $(PATH_VEC)ADTDef.h
	$(CC) $(CFLAGS) -c $(PATH_VEC)dynamicVector.c

heap.o: heap.c heap.h $(PATH_VEC)dynamicVector.h $(PATH_VEC)ADTDef.h
	$(CC) $(CFLAGS) -c heap.c
	
heapMain.o: heapMain.c heap.h $(PATH_VEC)dynamicVector.h $(PATH_VEC)ADTDef.h
	$(CC) $(CFLAGS) -c heapMain.c
	
clean:
	rm -f $(TARGET) $(OBJS)
