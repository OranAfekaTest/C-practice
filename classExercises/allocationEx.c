#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#define ARRLENGTH 100

void ArrInit(int *arr, int size);
void ArrPrint(int *arr, int size);
float recAvg(int *arr, int n, int i);
size_t recFibo(int n);
size_t itrFibo(int n);
void Hanoi(int _n, char _from, char _via, char _to);

int main(void)
{
	int* arr = (int*)malloc(ARRLENGTH * sizeof(int));
	if(arr)
	{
		ArrInit(arr, ARRLENGTH);
		ArrPrint(arr, ARRLENGTH);
		printf("\nrecursive maximum: %d\n",recMax(arr, ARRLENGTH));
		printf("\nrecursive avarage: %f\n",recAvg(arr, ARRLENGTH, 0));
		printf("\nrecursive fibonacci: %lu\n", recFibo(10));
		printf("\niterarive fibonacci: %lu\n", itrFibo(10));
		Hanoi(6,'A','B','C');
		free(arr);
	}
	
	
	return 0;
}

void ArrInit(int *arr, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		arr[i] = i;
	}
}


void ArrPrint(int *arr, int size)
{
	int i;
	putchar('[');
	for(i = 0; i < size; i++)
	{
		printf(" %d,", arr[i]);
	}
	putchar(']');
	putchar('\n');
}

float recAvg(int *arr, int n, int i)
{
	if(i == n - 1)
	{
		return arr[i];
	}
	if(i == 0)
		return (arr[i] + recAvg(arr, n, i + 1)) / n;
	
	return arr[i] + recAvg(arr, n, i + 1);
}

int recMax(int *arr, int n)
{
	if(n <= 1)
	{
		return arr[0];
	}
	
	return (recMax(arr,n - 1) < arr[n - 1] ? arr[n - 1] : recMax(arr,n - 1));
}

size_t recFibo(int n)
{
	if(n <= 0)
	{
	 return 1;
	}
	return recFibo(n - 1) + recFibo(n - 2);
}

size_t itrFibo(int n)
{
	size_t a = 1, b = 1, i, result;
	for(i = 0; i < n; i++)
	{
		result = a + b;
		a = b;
		b = result;
	}
	return result;
}

void Hanoi(int _n, char _from, char _via, char _to)
{
	if(_n == 1)
	{
		printf("%c -> %c\n", _from, _to);
		return;
	}
	Hanoi(_n - 1, _from, _to, _via);
	printf("%c -> %c\n", _from, _to);
	Hanoi(_n - 1, _via, _from, _to);
}
