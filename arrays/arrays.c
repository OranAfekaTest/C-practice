#include "arrays.h"
#define SWAP(A, B, T) T tmp = A;\
					  A = B;\
					  B = tmp;\


int MaxOccur(int _arr[], int _size)
{
	int i, j, counter = 0, result = 0;
	
	if(_size < 1)
		return SIZE_ERROR;
	
	for(i = 0; i < _size; i++)
	{
		for(j = 0; j < _size; j++)
		{
			if (_arr[i] == _arr[j])
			{
				counter++;
			}
		}
		if(counter > result)
			result = counter;
		counter = 0;
	}

	return result;
}

void Swap(int _arr[], int _a, int _b)
{
	int temp = _arr[_a];
	_arr[_a] = _arr[_b];
	_arr[_b] = temp;
}

void ShifRight(int _arr[], int _from, int _to)
{
	int temp = _arr[_from], i;
	for(i = _from; i > _to; i--)
	{
		_arr[i] = _arr[i - 1];
	}
	_arr[_to] = temp;
}

int OddSplit(int _arr[], int _size)
{
	int i, j, counter = 0;
	
	if(_size < 1)
		return SIZE_ERROR;
	
	counter += (_arr[0] % 2 == 0 ? 1 : 0); /* checks if th e first mamber is even */
	for(i = 1; i < _size; i++)
	{
		if(_arr[i] % 2 == 0)
		{
			ShifRight(_arr, i, counter);
			/*for(j = i; j > 0; j--)
			{
				if(_arr[j-1] % 2 != 0)
				{
					Swap(_arr, j, j-1);
					
				}
			}*/
			counter++;
		}
	}
	return counter;
}

int BubbleSort(int _arr[], int _size, fPtr f)
{
	int i, j, flag = 0;
	
	if(_size < 1)
		return SIZE_ERROR;
	
	for(i = 0; i < _size - 1; i++)
	{
		for(j = 0; j < _size - i - 1; j++)
		{
			if(f(_arr[j + 1], _arr[j]))
			{
				Swap(_arr, j, j + 1);
				flag = 1;
			}
		}
		if(!flag)
			break;
	}

	return OK;
}

int BubbleSortMacro(int _arr[], int _size)
{
	register int i, j, flag = 0;
	
	if(_size < 1)
		return SIZE_ERROR;
	
	for(i = 0; i < _size - 1; i++)
	{
		for(j = 0; j < _size - i - 1; j++)
		{
			if(_arr[j + 1] < _arr[j])
			{
				SWAP(_arr[j], _arr[j + 1], int);
				flag = 1;
			}
		}
		if(!flag)
			break;
	}

	return OK;
}


