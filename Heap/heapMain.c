#include "heap.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define ARBITRARY_INITIALIZATION_VALUE 4


int main(void)
{
	ADTErr err;
	Vector* vec;
	Heap* heap;
	int i, item;
	const char* str = "blabla";
	while(*str != '\0')
	{
		putchar(*str);
		str++;
	}
	putchar('\n');
	srand(time(NULL));
	vec = VectorCreate(ARBITRARY_INITIALIZATION_VALUE, ARBITRARY_INITIALIZATION_VALUE);
	
	for(i = 0; i < ARBITRARY_INITIALIZATION_VALUE * ARBITRARY_INITIALIZATION_VALUE; i++)
	{
		VectorAdd(vec, rand() % 50 + 1);
	}
	VectorPrint(vec);
	
	heap = HeapBuild(vec);
	err = HeapMax(heap, &item);
	if(err == ERR_OK)
	{
		printf("max = %d\n", item);
	}
	else
	{
		HandleErr(err, "");
	}
	HeapPrint(heap);
	/*
	void HeapDestroy(Heap* _heap);
printf("***reached***");
	ADTErr HeapInsert(Heap* _heap, int _data);

	ADTErr HeapMax(Heap* _heap, int* _data);

	ADTErr HeapExtractMax(Heap* _heap, int* _data);

	size_t HeapItemsNum(Heap* _heap);

	void HeapPrint(Heap* _heap);
	*/
	return 0;
}
