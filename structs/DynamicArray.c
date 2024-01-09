#include "DynamicArray.h"

DynamicArray* DynamicArrayCreate(int _size, int _blockSize)
{
	DynamicArray *arrHandler;
	if(!(_size || _blockSize) || _size < 0 || _blockSize < 0)
	{
		return NULL;
	}
	
	arrHandler = (DynamicArray*)malloc(sizeof(DynamicArray));
	
	if(!arrHandler)
	{
		return NULL;
	}
	
	arrHandler->dArray = (int*)malloc(sizeof(int) * _size);
	
	if(!(arrHandler->dArray))
	{
		free(arrHandler);
		return NULL;
	}
	
	arrHandler->dArraySize = _size;
	arrHandler->dArrayBlockSize = _blockSize;
	arrHandler->NumOfElements = 0;
	
	return arrHandler;
}

void DynamicArrayDestroy(DynamicArray** _DynaminArrayPtr)
{
	if(_DynaminArrayPtr*)
	{
		free((*_DynaminArrayPtr)->dArray);
		free((*_DynaminArrayPtr));
	}
	DynamicArray* = NULL;
}

int DynamicArrayInsert(DynamicArray* _DynaminArrayPtr,int _data)
{
	int *temPtr;
	if(_DynaminArrayPtr->NumOfElements < _DynaminArrayPtr->dArraySize)
	{
		_DynaminArrayPtr->dArray[_DynaminArrayPtr->NumOfElements] = _data;
		_DynaminArrayPtr->NumOfElements++;
		return OK;
	}
	else
	{
		if(_DynaminArrayPtr->dArrayBlockSize == 0)
		{
			return OVER_FLOW;
		}
		temPtr = (int*)realloc(_DynaminArrayPtr->dArray, (_DynaminArrayPtr->dArraySize + _DynaminArrayPtr->dArrayBlockSize) * sizeof(int));
		if(!temPtr)
		{
			return REALLOC_FAIL;
		}
		_DynaminArrayPtr->dArray = temPtr;
		_DynaminArrayPtr->dArray[_DynaminArrayPtr->NumOfElements] = _data;
		_DynaminArrayPtr->dArraySize += _DynaminArrayPtr->dArrayBlockSize;
		_DynaminArrayPtr->NumOfElements++;
		return OK;
	}
}

int DynamicArrayDelete(DynamicArray* _DynaminArrayPtr, int* _data)
{
	int* arr;
	int* endofArr;
	if (!(_DynaminArrayPtr || _data)
	{
		return NULL_POINTER;
	}
	
	arr = _DynaminArrayPtr->dArray;
	endofArr = &(arr[_DynaminArrayPtr->NumOfElements]);
	
	if(_data < arr || _DynaminArrayPtr->NumOfElements <= 0)
	{
		return UNDER_FLOW;
	}
	else if(_data > endofArr)
	{
		return OVER_FLOW;
	}
	while(_data < endofArr)
	{
		*_data = *(_data + 1);
		_data++;
	}
	_DynaminArrayPtr->NumOfElements--;
	return OK;
}
