#include "arrays.h"
#include <time.h>
#include <stdlib.h>
#define N 50000

static int cmp1 (int _a,int _b)
{
	return (_a < _b ? 1 : 0);
}

static int cmp2 (int _a,int _b)
{
	return (_b < _a ? 1 : 0);
}

static int cmp3 (int _a,int _b)
{
	return (_a % 2 == 0 ? 1 : 0);
}

static int cmp4 (int _a,int _b)
{
	return (_b % 2 == 0 ? 1 : 0);
}

void PrintArray(int _arr[], int _size)
{
	int i;
	putchar('[');
	for(i = 0; i < _size; i++)
	{
		printf(" %d,", _arr[i]);
	}
	putchar(']');
	putchar('\n');
}

int* GenerateIntArray(void)
{
	int i;
	int* arr = malloc(sizeof(int) * N);
	if(!arr)
	{
		return NULL;
	}
	for(i = 0; i < N; i++)
	{
		arr[i] = rand() % (N * 2);
	}
	return arr;
}

int main(void)
{

	int arr[] = {4, 4, 6, 2, 8, 4, 6, 3, 8, 5, 3, 8, 6, 4, 4};
	int size = sizeof(arr)/sizeof(arr[0]);
	int output = MaxOccur(arr, size);
	clock_t start_t, end_t;
	double total_t, totalMacro_t, improvment;
	int* bigArr = NULL;
	srand(time(NULL));
	bigArr = GenerateIntArray();
	
	
	printf("output of MaxOccur: %d\n", output);

	output = OddSplit(arr, size);

	printf("output of OddSplit: %d\n", output);
	PrintArray(arr, size);
	
	
	output = BubbleSort(arr, size, cmp1);
	printf("BubbleSort by cmp1: %d\n", output);
	PrintArray(arr, size);
	
	output = BubbleSort(arr, size, cmp2);
	printf("BubbleSort by cmp2: %d\n", output);
	PrintArray(arr, size);
	
	output = BubbleSort(arr, size, cmp3);
	printf("BubbleSort by cmp3: %d\n", output);
	PrintArray(arr, size);
	
	output = BubbleSort(arr, size, cmp4);
	printf("BubbleSort by cmp4: %d\n", output);
	PrintArray(arr, size);
	
	/*
	start_t = clock();
	output = BubbleSort(arr, size, NULL);
	end_t = clock();
	printf("output of BubbleSort: %d\n", output);
	PrintArray(arr, size);
	total_t = (double)(end_t - start_t);
	
	start_t = clock();
	output = BubbleSortMacro(arr, size);
	end_t = clock();
	totalMacro_t = (double)(end_t - start_t);
	improvment = (totalMacro_t / total_t) * 100;
	
	printf("improvment of BubbleSort in small array: %f\n", improvment);
	
	start_t = clock();
	output = BubbleSort(bigArr, N, NULL);
	end_t = clock();
	total_t = (double)(end_t - start_t);
	printf("total time of BubbleSort in big array: %f\n", total_t);

	bigArr = GenerateIntArray();
	
	start_t = clock();
	output = BubbleSortMacro(bigArr, N);
	end_t = clock();
	totalMacro_t = (double)(end_t - start_t);
	printf("total time of BubbleSortMacro in big array: %f\n", totalMacro_t);
	improvment = (totalMacro_t / total_t) * 100;
	
	printf("improvment of BubbleSort in big array: %f\n", improvment);
	*/
	return 0;
}
