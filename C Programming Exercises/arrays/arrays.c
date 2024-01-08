#include "arrays.h"


int MaxOccur(int _arr[], int _size)
{
	if(_size < 1)
		return SIZE_ERROR;
	int i, j, counter = 0, result = 0;
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


int OddSplit(int _arr[], int _size)
{
	if(_size < 1)
		return SIZE_ERROR;
	int i, j, counter = 0;
	counter += (_arr[0]%2==0?1:0); /* checks if th e first mamber is even */
	for(i = 1; i < _size; i++)
	{
		if(_arr[i] % 2 == 0)
		{
			counter++;
			for(j = i; j > 0; j--)
			{
				if(_arr[j-1] % 2 != 0)
				{
					Swap(_arr, j, j-1);
				}
			}
		}
	}
	return counter;
}

int BubbleSort(int _arr[], int _size)
{
	if(_size < 1)
		return SIZE_ERROR;
	int i, j, flag = 0;
	for(i = 0; i < _size - 1; i++)
	{
		for(j = 0; j < _size - i - 1; j++)
		{
			if(_arr[j + 1] < _arr[j])
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
