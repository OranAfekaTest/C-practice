#include "stack.h"
#include "dynamicVector.h"
#include <stdio.h>
#define MAGIC_NUMBER 16548

struct Stack
{
	Vector *m_vector;
	int m_magicNumber;
};

Stack* StackCreate (size_t _size, size_t _blockSize)
{
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	if(!stack)
	{
		return NULL;
	}
	stack->m_vector = VectorCreate(_size, _blockSize);
	if(!(stack->m_vector))
	{
		free(stack);
		return NULL;
	}
	stack->m_magicNumber = MAGIC_NUMBER;
	return stack;
}

void StackDestroy(Stack* _stack)
{
	if(!_stack)
	{
		return;
	}
	if(_stack->m_magicNumber == MAGIC_NUMBER)
	{
		_stack->m_magicNumber = 0;
		if(_stack->m_vector)
		{
			VectorDestroy(&(_stack->m_vector));
		}
		free(_stack);
	}
	_stack = NULL;
}

ADTErr StackPush (Stack* _stack, int _item)
{
	if(!_stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorAdd(_stack->m_vector, _item);
}

ADTErr StackPop (Stack* _stack, int* _item)
{
	if(!_stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete(_stack->m_vector, _item);
}

ADTErr StackTop (Stack* _stack, int* _item)
{
	ADTErr err;
	size_t numOfItems;
	if(!_stack || !_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_stack->m_vector, &numOfItems);
	if(err != ERR_OK)
	{
		return err;
	}
	return VectorGet(_stack->m_vector, numOfItems - 1, _item);
}

int StackIsEmpty(Stack* _stack)
{
	size_t numOfItems = 0;
	if(!_stack)
	{
		return FALSE;
	}
	VectorItemsNum(_stack->m_vector, &numOfItems);
	if(numOfItems == 0)
	{
		return TRUE;
	}
	return FALSE;
}

/* Unit-Test functions */

void StackPrint (Stack *_stack)
{
	int i;
	printf("\nStack:\n[");
	for(i = 0; i < _stack->m_vector->m_nItems; i++)
	{
		printf(" %d,", _stack->m_vector->m_items[i]);
	}
	printf("]\ncurrent size: %ld, number of items: %ld, block size: %ld.\n", _stack->m_vector->m_size, _stack->m_vector->m_nItems, _stack->m_vector->m_blockSize);
}
