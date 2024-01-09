#ifndef __STACK_H__
#define __STACK_H__
#define TRUE 1
#define FALSE 0
#include "ADTDef.h"
#include <stddef.h>


typedef struct Stack Stack;

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
Stack* StackCreate (size_t _size, size_t _blockSize);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
void StackDestroy(Stack* _stack);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
ADTErr StackPush (Stack* _stack, int _item);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
ADTErr StackPop (Stack* _stack, int* _item);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
ADTErr StackTop (Stack* _stack, int* _item);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
int StackIsEmpty(Stack* _stack);

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
/* Unit-Test functions */
void StackPrint (Stack *_stack);

#endif /*__STACK_H__*/
