#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamicVector.h"

#define ARBITRARY_INITIALIZATION_VALUE 4
#define N 50000

typedef int (*fPtr)(int, int);

ADTErr BubbleSort(Vector* _vec);
ADTErr ShakeSort(Vector* _vec);
ADTErr QuickSort(Vector* _vec);
ADTErr InsertionSort(Vector* _vec, size_t _gap, size_t _offset);
ADTErr SelectionSort(Vector* _vec);
ADTErr ShellSort(Vector* _vec);
ADTErr MergeSort(Vector* _vec);
ADTErr CountingSort(Vector* _vec, int _maxValue, fPtr f, int digitIndex);
ADTErr RadixSort(Vector* _vec, int _nDigits);
static void QuickRec(Vector* _vec, size_t _start, size_t _end);
static int partition(Vector* _vec, size_t _start, size_t _end);
static void MergeRec(Vector* _vec, int _left, int _right);
static void Merge(Vector* _vec, int _left, int _middle, int _right);
static int IsolateDigit(int _num, int _iDigit);

Vector* GenerateBigVector(void)
{
	int i;
	Vector* vec = VectorCreate(N, ARBITRARY_INITIALIZATION_VALUE);
	if(!vec)
	{
		return NULL;
	}
	for(i = 0; i < N; i++)
	{
		VectorAdd(vec, rand() % (N/ARBITRARY_INITIALIZATION_VALUE) + 1);
	}
	return vec;
}

int main(void)
{
	int i;
	clock_t start_t, end_t;
	double total_t;
	Vector* vec = VectorCreate(ARBITRARY_INITIALIZATION_VALUE, ARBITRARY_INITIALIZATION_VALUE);
	Vector* bigVec;
	ADTErr errNum;
	srand(time(NULL));
	for(i = 0; i < ARBITRARY_INITIALIZATION_VALUE * ARBITRARY_INITIALIZATION_VALUE; i++)
	{
		VectorAdd(vec, rand() % 90000 + 10000);
	}
	
	
	VectorPrint(vec);
	errNum = RadixSort(vec, 5);
	HandleErr(errNum, "");
	VectorPrint(vec);
	/*
	bigVec = GenerateBigVector();
	start_t = clock();
	ShakeSort(bigVec);
	end_t = clock();
	total_t = (double)(end_t - start_t);
	printf("Total time of ShakeSort: %f\n", total_t);
	*/
	bigVec = GenerateBigVector();
	start_t = clock();
	ShellSort(bigVec);
	end_t = clock();
	total_t = (double)(end_t - start_t);
	printf("Total time of ShellSort: %f\n", total_t/1000000);
	/*
	bigVec = GenerateBigVector();
	start_t = clock();
	QuickSort(bigVec);
	end_t = clock();
	total_t = (double)(end_t - start_t);
	printf("Total time of QuickSort: %f\n", total_t);
	
	bigVec = GenerateBigVector();
	start_t = clock();
	SelectionSort(bigVec);
	end_t = clock();
	total_t = (double)(end_t - start_t);
	printf("Total time of SelectionSort: %f\n", total_t);
	*/
	return 0;
}

ADTErr BubbleSort(Vector* _vec)
{
	int i, j, itemA, itemB, flag = 0;
	size_t numOfItems;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &numOfItems);
	if(err != ERR_OK)
	{
		return err;
	}
	
	for(i = 0; i < numOfItems - 1; i++)
	{
		for(j = 0; j < numOfItems - i - 1; j++)
		{
			VectorGet(_vec, j, &itemA);
			VectorGet(_vec, j + 1, &itemB);
			if(itemB < itemA)
			{
				VectorSet(_vec, j + 1, itemA);
				VectorSet(_vec, j, itemB);
				flag = 1;
			}
		}
		if(!flag)
			break;
	}

	return ERR_OK;
}

ADTErr ShakeSort(Vector* _vec)
{
	int i, start, end, itemA, itemB, flag = 0;
	size_t numOfItems;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &numOfItems);
	if(err != ERR_OK)
	{
		return err;
	}
	start = 0;
	end = numOfItems - 1;
	while(start < end)
	{
		for(i = start; i < end; i++)
		{
			VectorGet(_vec, i, &itemA);
			VectorGet(_vec, i + 1, &itemB);
			if(itemB < itemA)
			{
				VectorSet(_vec, i + 1, itemA);
				VectorSet(_vec, i, itemB);
				flag = 1;
			}
		}
		if(!flag)
			break;
		
		flag = 0;
		--end;
		
		for(i = end - 1; start <= i; i--)
		{
			VectorGet(_vec, i, &itemA);
			VectorGet(_vec, i + 1, &itemB);
			if(itemB < itemA)
			{
				VectorSet(_vec, i + 1, itemA);
				VectorSet(_vec, i, itemB);
				flag = 1;
			}
		}
		if(!flag)
			break;
		
		flag = 0;
		++start;
	}

	return ERR_OK;
}

ADTErr QuickSort(Vector* _vec)
{
	size_t start = 0, end;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &end);
	if(err != ERR_OK)
	{
		return err;
	}
	QuickRec(_vec, start, end - 1);
	return ERR_OK;
}

void QuickRec(Vector* _vec, size_t _start, size_t _end)
{
	size_t pivot;
	if(_start < _end)
	{
		pivot = partition(_vec, _start, _end);
		if(0 < pivot)
		{
			QuickRec(_vec, _start, pivot - 1);
		}
		QuickRec(_vec, pivot + 1, _end);
	}
}

int partition(Vector* _vec, size_t _start, size_t _end)
{
	int pivot, smallIndex = _start + 1, i, itemA, itemB;
	VectorGet(_vec, _start, &pivot);
	for(i = _start + 1; i <= _end; i++)
	{
		VectorGet(_vec, i, &itemA);
		if(itemA <= pivot)
		{
			VectorGet(_vec, smallIndex, &itemB);
			VectorSet(_vec, smallIndex, itemA);
			VectorSet(_vec, i, itemB);
			smallIndex++;
		}
	}
	VectorGet(_vec, smallIndex - 1, &itemB);
	VectorSet(_vec, smallIndex - 1, pivot);
	VectorSet(_vec, _start, itemB);

	return smallIndex - 1;
}

ADTErr InsertionSort(Vector* _vec, size_t _gap, size_t _offset)
{
	size_t i, j, size, bubbleLeft;
	int  itemA, itemB;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	for(i = 1*_gap + _offset; i < size; i += _gap)
	{
		bubbleLeft = i;
		
		while(_gap <= bubbleLeft)
		{
			err = VectorGet(_vec, bubbleLeft, &itemA);
			if(err != ERR_OK)
			{
				return err;
			}
			
			err = VectorGet(_vec, bubbleLeft - 1*_gap, &itemB);
			
			if(err != ERR_OK)
			{
				return err;
			}
			if(itemA < itemB)
			{
				err = VectorSet(_vec, bubbleLeft, itemB);
				if(err != ERR_OK)
				{
					return err;
				}
				
				err = VectorSet(_vec, bubbleLeft - 1*_gap, itemA);
				if(err != ERR_OK)
				{
					return err;
				}
				bubbleLeft -= _gap;
				
			}
			else
			{
				break;
			}
		}
	}
	return ERR_OK;
}

ADTErr SelectionSort(Vector* _vec)
{
	size_t size;
	int i, sortedIndex = 0, min, minIndex, unsortedItem;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	while(sortedIndex < size)
	{
		VectorGet(_vec, sortedIndex, &min);
		for(i = sortedIndex + 1; i < size; i ++)
		{
			VectorGet(_vec, i, &unsortedItem);
			if(unsortedItem < min)
			{
				min = unsortedItem;
				minIndex = i;
			}
		}
		VectorGet(_vec, sortedIndex, &unsortedItem);
		VectorSet(_vec, sortedIndex, min);
		VectorSet(_vec, minIndex, unsortedItem);
		sortedIndex++;
	}
	return ERR_OK;
}

ADTErr ShellSort(Vector* _vec)
{
	size_t size,  gap, i;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	gap = size;
	while(gap)
	{
		gap /= 2;
		for(i = 0; i < gap; i++)
		{
			err = InsertionSort(_vec, gap, i);
			if(err != ERR_OK)
			{
				return err;
			}
		}
	}
	
	return ERR_OK;
}

void Merge(Vector* _vec, int _left, int _middle, int _right)
{
	int leftIndex, rightIndex, mergedIndex;
	int leftN = _middle - _left + 1, rightN = _right - _middle;
	int *leftSubArr = (int*)malloc(leftN * sizeof(int));
	int *rightSubArr = (int*)malloc(rightN * sizeof(int));
	
	for(leftIndex = 0; leftIndex < leftN; leftIndex++)
	{
		VectorGet(_vec, _left + leftIndex, &leftSubArr[leftIndex]);
	}
	for(rightIndex = 0; rightIndex < rightN; rightIndex++)
	{
		VectorGet(_vec, _middle + 1 + rightIndex, &rightSubArr[rightIndex]);
	}
	
	leftIndex = 0;
	rightIndex = 0;
	mergedIndex = _left;
	
	while(leftIndex < leftN && rightIndex < rightN)
	{
		if(leftSubArr[leftIndex] <= rightSubArr[rightIndex])
		{
			VectorSet(_vec, mergedIndex, leftSubArr[leftIndex]);
			leftIndex++;
		}
		else
		{
			VectorSet(_vec, mergedIndex, rightSubArr[rightIndex]);
			rightIndex++;
		}
		mergedIndex++;
	}
	
	while(leftIndex < leftN)
	{
		VectorSet(_vec, mergedIndex, leftSubArr[leftIndex]);
		leftIndex++;
		mergedIndex++;
	}
	
	while(rightIndex < rightN)
	{
		VectorSet(_vec, mergedIndex, rightSubArr[rightIndex]);
		rightIndex++;
		mergedIndex++;
	}
	
	free(leftSubArr);
	free(rightSubArr);
}

void MergeRec(Vector* _vec, int _left, int _right)
{
	int middle;
	if(_left < _right)
	{
		middle = (_left + _right) / 2;
		
		MergeRec(_vec, _left, middle);
		MergeRec(_vec, middle + 1, _right);
		
		Merge(_vec, _left, middle, _right);
	}
}

ADTErr MergeSort(Vector* _vec)
{
	size_t size;
	ADTErr err;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	MergeRec(_vec, 0, size - 1);
	return ERR_OK;
}

ADTErr CountingSort(Vector* _vec, int _maxValue, fPtr f, int digitIndex)
{
	size_t size;
	ADTErr err;
	int item , i;
	int* accumulation, *result;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	accumulation = (int*)calloc((_maxValue + 1), sizeof(int));
	result = (int*)malloc(sizeof(int) * size);
	if(!_vec)
	{
		return ERR_ALLOCATION_FAILED;
	}
	for(i = 0; i < size; i++)
	{
		err = VectorGet(_vec, i, &item);
		if(err != ERR_OK)
		{
			return err;
		}
		accumulation[f(item, digitIndex)]++;
	}
	for(i = 1; i <= _maxValue; i++)
	{
		accumulation[i] += accumulation[i - 1];
	}
	for(i = size - 1; 0 <= i; i--)
	{
		err = VectorGet(_vec, i, &item);
		if(err != ERR_OK)
		{
			return err;
		}
		result[accumulation[f(item, digitIndex)] - 1] = item;
		accumulation[f(item, digitIndex)]--;
	}
	for(i = 0; i < size; i++)
	{
		err = VectorSet(_vec, i, result[i]);
		if(err != ERR_OK)
		{
			return err;
		}
	}
	free(accumulation);
	free(result);
	return ERR_OK;
}

ADTErr RadixSort(Vector* _vec, int _nDigits)
{
	size_t size;
	ADTErr err;
	int item , i;
	int* accumulation, *result;
	if(!_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	err = VectorItemsNum(_vec, &size);
	if(err != ERR_OK)
	{
		return err;
	}
	for(i = 0; i < _nDigits; i++)
	{
		CountingSort(_vec, 9, IsolateDigit, i);
	}
	return ERR_OK;
}

int IsolateDigit(int _num, int _iDigit)
{
	return (int)(_num / pow(10, _iDigit)) % 10;
}
