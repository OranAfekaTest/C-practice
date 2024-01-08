#include <stdio.h>
#include <math.h>
#define SIZE_ERROR -1
#define OK 0

typedef int (*fPtr)(int, int);

/* description - counts the maximum occurances of a single intager within the array
input- an array of integers and his size
output- the maximun occurances of a single number in the array
errors- 1: size is out of bounds */
int MaxOccur(int _arr[], int _size);

/* description - sorting array to even first, after them the odd 
while keepin thier order
input- an array of integers and his size
output- the number of even numbers or Error
errors- 1: size is out of bounds */
int OddSplit(int _arr[], int _size);

/* description - sorting an array of integers in ascending order
input- an array of integers and his size
output- status OK or Error
errors- 1: size is out of bounds */
int BubbleSort(int _arr[], int _size, fPtr);
int BubbleSortMacro(int _arr[], int _size);
