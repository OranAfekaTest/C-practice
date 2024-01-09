#include "heap.h"
#include <stdio.h>
#define MAGIC_NUMBER 98647
#define PARENT(i) (i - 1) / 2
#define LEFT_CHILD(i) (2 * (i) + 1)
#define RIGHT_CHILD(i) (2 * (i) + 2)

struct Heap
{
Vector* m_vec;
size_t m_heapSize;
int m_magicNumber;
};

static void BubbleUp(Heap* _heap, int _index);
static void Heapify(Heap* _heap, int _index);

Heap* HeapBuild(Vector* _vec)
{
	int i;
	Heap* heap = NULL;
	if(!_vec)
	{
		return NULL;
	}
	heap = malloc(sizeof(Heap));
	if(!heap)
	{
		return NULL;
	}
	heap->m_vec = _vec;
	heap->m_heapSize = VectorGetNumOfItems(_vec);
	heap->m_magicNumber = MAGIC_NUMBER;	
	for( i  = heap->m_heapSize/2; 0 <= i; i--)
	{
		Heapify(heap, i);
	}
	return heap;
}

void HeapDestroy(Heap* _heap)
{
	if(!_heap)
	{
		return;
	}
	if(_heap->m_magicNumber == MAGIC_NUMBER)
	{
		_heap->m_magicNumber = 0;
		_heap->m_vec = NULL;
		free(_heap);
	}
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	ADTErr err = ERR_OK;
	if(!_heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorAdd(_heap->m_vec, _data);
	if(err != ERR_OK)
	{
		return err;
	}
	BubbleUp(_heap, _heap->m_heapSize);
	_heap->m_heapSize++;
	return ERR_OK;
}

ADTErr HeapMax(Heap* _heap, int* _data)
{
	if(!_heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorGet(_heap->m_vec, 0, _data);
}

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	ADTErr err;
	int lastItem;
	if(!_heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorGet(_heap->m_vec, 0, _data);
	if(err != ERR_OK)
	{
		return err;
	}
	err = VectorDelete(_heap->m_vec, &lastItem);
	if(err != ERR_OK)
	{
		return err;
	}
	err = VectorSet(_heap->m_vec, 0, lastItem);
	if(err != ERR_OK)
	{
		return err;
	}
	Heapify(_heap, 0);
	_heap->m_heapSize--;
	return ERR_OK;
}

size_t HeapItemsNum(Heap* _heap)
{
	if(!_heap)
	{
		return -1;
	}
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	int i, item;
	if(!_heap)
	{
		return;
	}
	printf("Heap size: %ld, Items:\n[", _heap->m_heapSize);
	for(i = 0; i < _heap->m_heapSize; i++)
	{
		VectorGet(_heap->m_vec, i, &item);
		printf(" %d,", item);
	}
	putchar(']');
	putchar('\n');
}

void BubbleUp(Heap* _heap, int _index)
{
	int tmp, parent, current;
	int* items;
	if(_index == 0)
	{
		return;
	}
	
	VectorGet(_heap->m_vec, _index, &current);
	VectorGet(_heap->m_vec, PARENT(_index), &parent);
	
	if(parent < current)
	{
		VectorSet(_heap->m_vec, _index, parent);
		VectorSet(_heap->m_vec, PARENT(_index), current);
		BubbleUp(_heap, PARENT(_index));
	}
}

void Heapify(Heap* _heap, int _index)
{
	int left, right, parent, largest;
	
	VectorGet(_heap->m_vec, _index, &parent);
	VectorGet(_heap->m_vec, LEFT_CHILD(_index), &left);
	
	largest = (parent < left ? left : parent);
	if(VectorGet(_heap->m_vec, RIGHT_CHILD(_index), &right) == ERR_OK && parent < right && left < right)
	{
		largest = right;
	}
	if(largest != parent)
	{
		VectorSet(_heap->m_vec, _index, largest);
		VectorSet(_heap->m_vec, (largest == left ? LEFT_CHILD(_index) : RIGHT_CHILD(_index)), parent);
		Heapify(_heap, (largest == left ? LEFT_CHILD(_index) : RIGHT_CHILD(_index)));
	}
}
