#include "dynamicVector.h"
#include <stdio.h>

struct Vector
{
int* m_items;
size_t m_originalSize; /* original allocated space for items */
size_t m_size; /* actual allocated space for items*/
size_t m_nItems; /* actual number of items */
size_t m_blockSize; /* the chunk size to be allocated when no space*/
};

ADTErr IncreaseVector(Vector *_veVectorGetNumOfItemsctor);
ADTErr DecreaseVector(Vector *_vector);

Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
	Vector* vec;
	
	if(!(_initialSize || _extensionBlockSize) || _initialSize < 0 || _extensionBlockSize < 0)
	{
		return NULL;
	}
	
	vec = (Vector*)malloc(sizeof(Vector));
	
	if(!vec)
	{
		return NULL;
	}
	
	vec->m_items = (int*)malloc(sizeof(int*) * _initialSize);
	
	if(!(vec->m_items))
	{
		free(vec);
		return NULL;
	}
	
	vec->m_originalSize = _initialSize;
	vec->m_size = _initialSize;
	vec->m_blockSize = _extensionBlockSize;
	vec->m_nItems = 0;
	
	return vec;
}

void VectorDestroy(Vector** _vector)
{
	if(*_vector)
	{
		free((*_vector)->m_items);
		free((*_vector));
	}
	*_vector = NULL;
}

ADTErr VectorAdd(Vector *_vector, int _item)
{
	ADTErr status;
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(!(_vector->m_nItems < _vector->m_size))
	{
		status = IncreaseVector(_vector);
		if(status != ERR_OK)
		{
			return status;
		}
	}
	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems++;
	return ERR_OK;
}

ADTErr VectorDelete(Vector *_vector, int* _item)
{
	ADTErr status;
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector->m_nItems <= 0)
	{
		return ERR_UNDERFLOW;
	}
	(_vector->m_nItems)--;
	*_item = _vector->m_items[_vector->m_nItems];
	if(_vector->m_size - _vector->m_nItems > 2 * _vector->m_blockSize)
	{
		status = DecreaseVector(_vector);
	}
	return status;
}

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index < 0 || _vector->m_nItems <= _index)
	{
		return ERR_WRONG_INDEX;
	}
	*_item = _vector->m_items[_index];
	return ERR_OK;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index < 0 || _vector->m_nItems <= _index)
	{
		return ERR_WRONG_INDEX;
	}
	_vector->m_items[_index] = _item;
	return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems)
{
	if(!_vector || !_numOfItems)
	{
		return ERR_NOT_INITIALIZED;
	}
	*_numOfItems = _vector->m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector *_vector)
{
	int i;
	printf("\nVector:\n[");
	for(i = 0; i < _vector->m_nItems; i++)
	{
		printf(" %d,",_vector->m_items[i]);
	}
	printf("]\noriginal size: %ld, current size: %ld, number of items: %ld, block size: %ld.\n",_vector->m_originalSize, _vector->m_size, _vector->m_nItems, _vector->m_blockSize);
}

ADTErr IncreaseVector(Vector *_vector)
{
	int *temPtr;
	if(_vector->m_blockSize == 0)
	{
		return ERR_OVERFLOW;
	}
	temPtr = (int*)realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize) * sizeof(int));
	if(!temPtr)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temPtr;
	_vector->m_size += _vector->m_blockSize;
	return ERR_OK;
}

ADTErr DecreaseVector(Vector *_vector)
{
	int *temPtr;
	if(_vector->m_blockSize == 0)
	{
		return ERR_UNDERFLOW;
	}
	temPtr = (int*)realloc(_vector->m_items, (_vector->m_size - _vector->m_blockSize) * sizeof(int));
	if(!temPtr)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temPtr;
	_vector->m_size -= _vector->m_blockSize;
	return ERR_OK;
}

/* Getters */
int* VectorGetItems(Vector *_vector)
{
	if(!_vector)
	{
		return NULL;
	}
	return _vector->m_items;
}

size_t VectorGetOriginalSize(Vector *_vector)
{
	if(!_vector)
	{
		return -1;
	}
	return _vector->m_originalSize;
}

size_t VectorGetSize(Vector *_vector)
{
	if(!_vector)
	{
		return -1;
	}
	return _vector->m_size;
}

size_t VectorGetNumOfItems(Vector *_vector)
{
	if(!_vector)
	{
		return -1;
	}
	return _vector->m_nItems;
}

size_t VectorGetBlockSize(Vector *_vector)
{
	if(!_vector)
	{
		return -1;
	}
	return _vector->m_blockSize;
}
