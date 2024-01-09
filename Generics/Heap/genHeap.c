#include "genHeap.h"
#define PARENT(i) (i - 1) / 2
#define LEFT_CHILD(i) (2 * (i) + 1)
#define RIGHT_CHILD(i) (2 * (i) + 2)

struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	LessThanComparator m_pfLess;
};

static void BubbleUp(Heap* _heap, size_t _index);
static void Heapify(Heap* _heap, size_t _index);

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	size_t i;
	Heap* heap = NULL;
	if(!_vector)
	{
		return NULL;
	}
	heap = malloc(sizeof(Heap));
	if(!heap)
	{
		return NULL;
	}
	heap->m_vec = _vector;
	heap->m_heapSize = VectorSize(_vector);
	heap->m_pfLess = _pfLess;
	
	for(i  = heap->m_heapSize / 2; 0 < i; --i)
	{
		Heapify(heap, i - 1);	
	}

	return heap;
}

Vector* HeapDestroy(Heap** _heap)
{
	Vector* vec = NULL;
	if(*_heap)
	{
		vec = (*_heap)->m_vec;
		free(*_heap);
		*_heap = NULL;
	}
	return vec;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
	HeapResultCode result;
	if(!_heap || !_element)
	{
		return HEAP_NOT_INITIALIZED;
	}
	result = VectorAppend(_heap->m_vec, _element);
	if(result != HEAP_SUCCESS)
	{
		return result;
	}
	BubbleUp(_heap, _heap->m_heapSize);
	_heap->m_heapSize++;
	return HEAP_SUCCESS;
}

const void* HeapPeek(const Heap* _heap)
{
	void* element = NULL;
	if(!_heap)
	{
		return NULL;
	}
	VectorGet(_heap->m_vec, 0, &element);
	return element;
}

void* HeapExtract(Heap* _heap)
{
	void* element = NULL, *lastItem = NULL;
	if(!_heap)
	{
		return NULL;
	}
	HandleVectorResult(VectorGet(_heap->m_vec, 0, &element));
	if(!element)
	{
		puts("NULL element at HeapExtract");
		return NULL;
	}
	VectorRemove(_heap->m_vec, &lastItem);
	if(!lastItem)
	{
		puts("NULL lastItem at HeapExtract");
	}
	
	VectorSet(_heap->m_vec, 0, lastItem);
	
	Heapify(_heap, 0);
	_heap->m_heapSize--;
	return element;
}

size_t HeapSize(const Heap* _heap)
{
	if(!_heap)
	{
		return -1;
	}
	return _heap->m_heapSize;
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t i;
	void* elem = NULL;
	if(!_heap)
	{
		return 0;
	}
	for(i = 0; i < _heap->m_heapSize; ++i)
	{
		VectorGet(_heap->m_vec, i, &elem);
		if(!elem || _act(elem, _context) == 0)
		{
			break;
		}

	}
	return i;
}

void BubbleUp(Heap* _heap, size_t _index)
{
	void* tmp, *parent, *current;
	if(_index == 0)
	{
		return;
	}
	
	VectorGet(_heap->m_vec, _index, &current);
	VectorGet(_heap->m_vec, PARENT(_index), &parent);
	
	if(_heap->m_pfLess(parent, current))
	{
		VectorSet(_heap->m_vec, _index, parent);
		VectorSet(_heap->m_vec, PARENT(_index), current);
		BubbleUp(_heap, PARENT(_index));
	}
}

void Heapify(Heap* _heap, size_t _index)
{
	void* left = NULL, *right = NULL, *parent = NULL , *largest = NULL;

	VectorGet(_heap->m_vec, _index, &parent);
	VectorGet(_heap->m_vec, LEFT_CHILD(_index), &left);
	if(!parent || !left)
	{
		return;
	}

	largest = (_heap->m_pfLess(parent, left) ? left : parent);
	if(!VectorGet(_heap->m_vec, RIGHT_CHILD(_index), &right) && _heap->m_pfLess(parent, right) && _heap->m_pfLess(left, right))
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

