#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stddef.h>
#define TRUE 1
#define FALSE 0


typedef struct Queue Queue;

/* description - creates a queue of integers by given length.
output- Pointer to the queue handler
errors- illigal sizes inputs will return NULL */
Queue* QueueCreate(size_t _size);

/* description - frees memmory space of a queue.
output- None.
errors- None. */
void QueueDestroy(Queue *_queue);

/* description - inserts and item to queue.
output- errors
errors- 1: ERR_NOT_INITIALIZED
		2: ERR_OVERFLOW
		3: ERR_OK */
ADTErr QueueInsert(Queue *_queue, int _item);

/* description - takes the first item out of the queue and put it in _item.
output- errors
errors- 1: ERR_NOT_INITIALIZED
		2: ERR_UNDERFLOW
		3: ERR_OK */
ADTErr QueueRemove(Queue *_queue, int *_item);

/* description - tells you if queue is empty.
output- True or False.
errors- None. */
Int QueueIsEmpty(Queue *_queue);

/* description - prints the queue, items and information.
output- None.
errors- None. */
void QueuePrint(Queue *_queue);

#endif /*__QUEUE_H__*/
