#include "GenSort.h"
#define OK 0
#define ERROR 1
#define NEXT _elements + (j + 1) * _elementSize
#define CURRENT _elements + j * _elementSize

void GenSwap(void* _tmp, void* _a, void* _b, size_t _elementSize)
{
	memcpy(_tmp, _a, _elementSize);
	memcpy(_a, _b, _elementSize);
	memcpy(_b, _tmp, _elementSize);
}

int GenSort(void* _elements, size_t _elementSize, size_t _size, int(*_criteria)(const void* _a, const void* _b))
{
	int i, j, flag = 0;
	void* tmp = malloc(_elementSize);
	if(_size < 1 || _elementSize < 1 || !_elements || !tmp)
	{
		return ERROR;
	}
	
	
	for(i = 0; i < _size - 1; i++)
	{
		for(j = 0; j < _size - i - 1; j++)
		{
			if(_criteria(NEXT, CURRENT))
			{
				GenSwap(tmp, NEXT, CURRENT);
				flag = 1;
			}
		}
		if(!flag)
			break;
	}
	free(tmp);
	return OK;
}
