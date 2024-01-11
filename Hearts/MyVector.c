#include "MyVector.h"


struct Vector
{
	void** m_items;
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size; /* actual allocated space for items*/
	size_t m_nItems; /* actual number of items */
	size_t m_blockSize; /* the chunk size to be allocated when no space*/
};

static VectorResult IncreaseVector(Vector *_vector);
static VectorResult DecreaseVector(Vector *_vector);

const char* resultDescription[] =
{
	"Success",
	"Uninitialized vector",
	"Allocation error",
	"Index out of bounds",
	"Vector is not dynamic",
	"Item is Null",
	"Vector is empty",
	"General Error",
};

void HandleVectorResult(VectorResult resultNum)
{
	if(resultNum) 
	{
		printf("Result number=%d, Result description=%s\n",
		resultNum, resultDescription[resultNum]);
	}
}

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector* vec;
	
	if(!(_initialCapacity || _blockSize) || _initialCapacity < 0 || _blockSize < 0)
	{
		return NULL;
	}
	
	vec = (Vector*)malloc(sizeof(Vector));
	
	if(!vec)
	{
		return NULL;
	}
	
	vec->m_items = (void**)malloc(sizeof(void*) * _initialCapacity);
	
	if(!(vec->m_items))
	{
		free(vec);
		return NULL;
	}
	
	vec->m_originalSize = _initialCapacity;
	vec->m_size = _initialCapacity;
	vec->m_blockSize = _blockSize;
	vec->m_nItems = 0;
	
	return vec;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void** _item))
{
	size_t i;
	if(*_vector)
	{
		if(_elementDestroy)
		{
			for(i = 0; i < (*_vector)->m_nItems; i++)
			{
				_elementDestroy(&((*_vector)->m_items[i]));
			}
		}
		free((*_vector)->m_items);
		free((*_vector));
	}
	*_vector = NULL;
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
	VectorResult result;
	if(!_vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(!_item)
	{
		return VECTOR_NULL_ITEM;
	}
	if(!(_vector->m_nItems < _vector->m_size))
	{
		result = IncreaseVector(_vector);
		if(result != VECTOR_SUCCESS)
		{
			return result;
		}
	}
	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems++;
	return VECTOR_SUCCESS;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	VectorResult result;
	if(!_vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(!_pValue)
	{
		return VECTOR_NULL_ITEM;
	}
	if(_vector->m_nItems <= 0)
	{
		return VECTOR_EMPTY;
	}
	(_vector->m_nItems)--;
	*_pValue = _vector->m_items[_vector->m_nItems];
	if(_vector->m_blockSize && (_vector->m_size - _vector->m_nItems > 2 * _vector->m_blockSize))
	{
		result = DecreaseVector(_vector);
		if(result != VECTOR_SUCCESS)
		{
			return result;
		}
	}
	return VECTOR_SUCCESS;
}

VectorResult VectorRemoveByIndex(Vector* _vector,size_t _index, void** _pValue)
{
	VectorResult result;
	size_t i;
	if(!_vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(!_pValue)
	{
		return VECTOR_NULL_ITEM;
	}
	if(_vector->m_nItems <= 0)
	{
		return VECTOR_EMPTY;
	}
	if(_index < 0 || _vector->m_nItems <= _index)
	{
		printf("index:%ld nItems:%ld", _index, _vector->m_nItems);
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	*_pValue = _vector->m_items[_index];
	(_vector->m_nItems)--;
	for(i = _index; i < _vector->m_nItems; i++)
	{
		_vector->m_items[i] = _vector->m_items[i + 1];
	}
	return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	if(!_vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(!_pValue)
	{
		return VECTOR_NULL_ITEM;
	}
	if(_index < 0 || _vector->m_nItems <= _index)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	*_pValue = _vector->m_items[_index];
	return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	if(!_vector)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(!_value)
	{
		return VECTOR_NULL_ITEM;
	}
	if(_index < 0 || _vector->m_nItems <= _index)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector->m_items[_index] = _value;
	return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector)
{
	if(!_vector)
	{
		return 0;
	}
	return _vector->m_nItems;
}

size_t VectorCapacity(const Vector* _vector)
{
	if(!_vector)
	{
		return 0;
	}
	return _vector->m_size;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	size_t i;
	void* elem = NULL;
	if(!_vector)
	{
		return 0;
	}
	for(i = 0; i < VectorSize(_vector); ++i)
	{
		VectorGet(_vector, i, &elem);
		if(!elem || _action(elem, i, _context) == 0)
		{
			break;
		}

	}
	return i;
}

size_t VectorGetByCriteria(const Vector* _vector, VectorComparator _comparator, void** _outputItem)
{
	size_t i = 0, outputIndex;
	void* result = NULL;
	void* cmpItem = NULL;
	if(!_vector)
	{
		return -1;
	}

	result = _vector->m_items[i];
	for(i = 1; i < VectorSize(_vector); ++i)
	{
		VectorGet(_vector, i, &cmpItem);
		if(_comparator(result, cmpItem))
		{
			result = cmpItem;
			outputIndex = i;
		}
	}
	if(_outputItem)
	{
		*_outputItem = result;
	}
	
	return outputIndex;
}

VectorResult IncreaseVector(Vector *_vector)
{
	void** temPtr;
	size_t i, size = _vector->m_size + _vector->m_blockSize;
	if(_vector->m_blockSize == 0)
	{
		return VECTOR_NOT_DYNAMIC;
	}
	temPtr = (void**)realloc(_vector->m_items, size * sizeof(void*));
	if(!temPtr)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	for(i = 0; i < _vector->m_blockSize; i++)
	{
		temPtr[_vector->m_size + i] = NULL;
	}
	_vector->m_items = temPtr;
	_vector->m_size += _vector->m_blockSize;
	return VECTOR_SUCCESS;
}

VectorResult DecreaseVector(Vector *_vector)
{
	void** temPtr;
	if(_vector->m_blockSize == 0)
	{
		return VECTOR_NOT_DYNAMIC;
	}
	temPtr = (void**)realloc(_vector->m_items, (_vector->m_size - _vector->m_blockSize) * sizeof(void*));
	if(!temPtr)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	_vector->m_items = temPtr;
	_vector->m_size -= _vector->m_blockSize;
	return VECTOR_SUCCESS;
}
