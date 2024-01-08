#include "arrays.h"

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

int main(void)
{

	int arr[] = {4, 4, 6, 2, 8, 4, 6, 3, 8, 5, 3, 8, 6, 4, 4};
	int size = sizeof(arr)/sizeof(arr[0]);


	int output = MaxOccur(arr, size);

	printf("output of MaxOccur: %d\n", output);

	output = OddSplit(arr, size);

	printf("output of OddSplit: %d\n", output);
	PrintArray(arr, size);

	output = BubbleSort(arr, size);
	printf("output of BubbleSort: %d\n", output);
	PrintArray(arr, size);

	return 0;
}