#include "queue.h"
#include "/h74/DynamicVector/ADTDef.h"
#define MAGIC_NUMBER 26548

struct Queue
{
int* m_que;
size_t m_size;
size_t m_head; /* Index of head in m_que. */
size_t m_tail; /* Index of tail in m_que. */
size_t m_nItems;
int m_magicNumber;
};

Queue* QueueCreate(size_t _size)
{
	Queue* newQueue = NULL;
	newQueue = (Queue*)malloc(sizeof(Queue));
	if(!newQueue)
	{
		return NULL;
	}
	if(_size < 1)
	{
		return NULL;
	}
	newQueue->m_que = (int*)malloc(sizeof(int) * _size);
	if(!newQueue->m_que)
	{
		free(newQueue);
		return NULL;
	}
	newQueue->m_size = _size;
	newQueue->m_head = 0;
	newQueue->m_tail = 0;
	newQueue->m_nItems = 0;
	newQueue->m_magicNumber = MAGIC_NUMBER;
	return newQueue;
}

void QueueDestroy(Queue *_queue)
{
	if(!_queue)
	{
		return;
	}
	if(_queue->m_magicNumber == MAGIC_NUMBER)
	{
		_queue->m_magicNumber = 0;
		if(_queue->m_que)
		{
			free(_queue->m_que);
		}
		free(_queue);
	}
}

ADTErr QueueInsert(Queue *_queue, int _item)
{
	if(!_queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_queue->m_nItems < _queue->m_size)
	{
		_queue->m_que[_queue->m_tail] = _item;
		_queue->m_tail = (_queue->m_tail +  1) % _queue->m_size;
		_queue->m_nItems++;
	}
	else
	{
	 return ERR_OVERFLOW;
	}
	return ERR_OK;
}

ADTErr QueueRemove(Queue *_queue, int *_item)
{
	if(!_queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_queue->m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	*_item = _queue->m_que[_queue->m_head];
	_queue->m_head = (_queue->m_head +  1) % _queue->m_size;
	_queue->m_nItems--;
	return ERR_OK;
}

Int QueueIsEmpty(Queue *_queue)
{
	if(_queue->m_nItems == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void QueuePrint(Queue *_queue)
{
	int i;
	printf("\nQueue:\n[");
	for(i = 0; i < _queue->m_nItems; i++)
	{
		printf(" %d,", _queue->m_que[(_queue->m_head + i) % _queue->m_size]);
	}
	printf("]\ncurrent size: %ld, number of items: %ld, head is at: %ld, tail is at: %ld.\n", _queue->m_size, _queue->m_nItems, _queue->m_head, _queue->m_tail);
}
