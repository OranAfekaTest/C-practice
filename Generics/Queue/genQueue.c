#include "genQueue.h"
#include <stdlib.h>		/*for size_t*/

struct Queue
{
	void** m_que;
	size_t m_size;
	size_t m_head; /* Index of head in m_que. */
	size_t m_tail; /* Index of tail in m_que. */
	size_t m_nItems;

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
	newQueue->m_que = malloc(sizeof(void**) * _size);
	if(!newQueue->m_que)
	{
		free(newQueue);
		return NULL;
	}
	newQueue->m_size = _size;
	newQueue->m_head = 0;
	newQueue->m_tail = 0;
	newQueue->m_nItems = 0;
	return newQueue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t i;
	if(*_queue)
	{
		for(i = 0; i < (*_queue)->m_nItems; i += sizeof(void*))
		{
			_itemDestroy(*((*_queue)->m_que + i));
		}
		free((*_queue)->m_que);
		free(*_queue);
		*_queue = NULL;
	}
}

QueueResult QueueInsert(Queue* _queue,void* _item)
{
	if(!_queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(!_item)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems < _queue->m_size)
	{
		_queue->m_que[_queue->m_tail] = _item;
		_queue->m_tail = (_queue->m_tail +  1) % _queue->m_size;
		_queue->m_nItems++;
	}
	else
	{
	 return QUEUE_OVERFLOW_ERROR;
	}
	return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue,void** _item)
{
	if(!_queue)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(!_item)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems == 0)
	{
		return QUEUE_DATA_NOT_FOUND_ERROR;
	}
	*_item = _queue->m_que[_queue->m_head];
	_queue->m_head = (_queue->m_head +  1) % _queue->m_size;
	_queue->m_nItems--;
	return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue)
{
	if(_queue->m_nItems == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	size_t result, i, counter = 0;
	if(!_queue || !_action)
	{
		return counter;
	}
	i = _queue->m_head;
	while(i != _queue->m_tail)
	{
		result = _action( _queue->m_que[i], _context);
		if(!result)
		{
			break;
		}
		counter++;
		i = (i + 1) % _queue->m_size;
	}
	return counter; 
}

