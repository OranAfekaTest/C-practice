# Generic Strutture Library makefile 

TARGET= libGenerics.so
CC= gcc
CFLAGS= -fPIC
OBJS= genBST.o hashMap.o genHeap.o genList.o listItr.o listFunctions.o genQueue.o genVector.o 

$(TARGET): $(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	
genBST.o: BST/genBST.c BST/genBST.h
	$(CC) $(CFLAGS) -c BST/genBST.c

hashMap.o: Hash/hashMap.c Hash/hashMap.h
	$(CC) $(CFLAGS) -c Hash/hashMap.c

genHeap.o: Heap/genHeap.c Heap/genHeap.h
	$(CC) $(CFLAGS) -c Heap/genHeap.c

genList.o: List/genList.c List/genList.h List/listInternal.h
	$(CC) $(CFLAGS) -c List/genList.c

listItr.o: List/listItr.c List/listItr.h List/listInternal.h
	$(CC) $(CFLAGS) -c List/listItr.c

listFunctions.o: List/listFunctions.c List/listFunctions.h List/listItr.h
	$(CC) $(CFLAGS) -c List/listFunctions.c

genQueue.o: Queue/genQueue.c Queue/genQueue.h
	$(CC) $(CFLAGS) -c Queue/genQueue.c

genVector.o: Vector/genVector.c Vector/genVector.h
	$(CC) $(CFLAGS) -c Vector/genVector.c

clean:
	rm -f $(TARGET) $(OBJS)

