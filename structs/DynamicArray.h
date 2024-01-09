#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define OK 1
#define NULL_POINTER 2
#define OVER_FLOW 3
#define REALLOC_FAIL 4
#define UNDER_FLOW 5

struct DynamicArray
{
int *dArray;
int dArraySize;
int dArrayBlockSize;
int NumOfElements;
} typedef DynamicArray;

/* description - creates a dynamic array of integer of given length.
output- Pointer to the array dynamic handler
errors- illigal sizes unputs will return NULL */
DynamicArray* DynamicArrayCreate(int _size,int _blockSize);

/* description - frees space of given dynamic array and its handler. 
output- None.
errors- None. */
void DynamicArrayDestroy(DynamicArray** _DynaminArrayPtr);

/* description - insert a memmber to a dynamic array.
output- OK or Errors
errors- 3: OVER_FLOW
	4: REALLOC_FAIL */
int DynamicArrayInsert(DynamicArray* _DynaminArrayPtr,int _data);

/* description - deletes a specific member of a dynamic array
output- OK or Errors
errors- 3: OVER_FLOW
	5: UNDER_FLOW  */
int DynamicArrayDelete(DynamicArray* _DynaminArrayPtr,int* _data);
