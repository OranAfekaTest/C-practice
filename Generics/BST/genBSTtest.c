#include "genBST.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAX_VAL 50
#define LENGTH 16

static int IntComparator(void* _left, void* _right);
static int* InitIntArray(size_t _length, int _maxVal);

int main(void)
{
    size_t i;
    BSTree* tree =  BSTreeCreate(IntComparator);
    BSTreeItr itr = NULL;
    int* arr = InitIntArray(LENGTH, MAX_VAL);
    for(i = 0; i < LENGTH; i++)
    {
        printf("Inserting %d into tree\n", arr[i]);
        itr = BSTreeInsert(tree, arr + i);
    }


    
    BSTreeDestroy(&tree, NULL);
    free(arr);
    return 0;
}

int* InitIntArray(size_t _length, int _maxVal)
{
    size_t i;
    int* arr = malloc(_length * sizeof(int));
    srand(time(NULL));
    for(i = 0; i < _length; i++)
    {
        arr[i] = rand() % MAX_VAL;
    }
    return arr;
}

int IntComparator(void* _left, void* _right)
{
    return *(int*)_left < *(int*)_right;
}
