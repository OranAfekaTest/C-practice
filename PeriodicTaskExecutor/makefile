# Periodic Task Executor makefile

TARGET= PTE.out
CC= gcc
VECTORPATH= ../Generics/Vector/
HEAPPATH= ../Generics/Heap/
CFLAGS= -D_GNU_SOURCE -D_POSIX_C_SOURCE=199309L -ansi -g -pedantic
OBJS= genVector.o genHeap.o CalcTime.o Task.o PeriodicExecutor.o PeriodicTaskExecutorTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
genVector.o: $(VECTORPATH)genVector.c $(VECTORPATH)genVector.h
	$(CC) $(CFLAGS) -c $(VECTORPATH)genVector.c
	
genHeap.o: $(HEAPPATH)genHeap.c $(HEAPPATH)genHeap.h $(VECTORPATH)genVector.h
	$(CC) $(CFLAGS) -c $(HEAPPATH)genHeap.c

CalcTime.o: CalcTime.c CalcTime.h
	$(CC) $(CFLAGS) -c CalcTime.c

Task.o: Task.c Task.h CalcTime.h
	$(CC) $(CFLAGS) -c Task.c

PeriodicExecutor.o: PeriodicExecutor.c PeriodicExecutor.h $(HEAPPATH)genHeap.h Task.h
	$(CC) $(CFLAGS) -c PeriodicExecutor.c

PeriodicTaskExecutorTest.o: PeriodicTaskExecutorTest.c PeriodicExecutor.h
	$(CC) $(CFLAGS) -c PeriodicTaskExecutorTest.c
	
clean:
	rm -f $(TARGET) $(OBJS)
