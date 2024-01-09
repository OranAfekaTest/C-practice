#ifndef __HEAP_P__
#define __HEAP_P__
#include <stddef.h>
#include "../DynamicVector/ADTDef.h"
#include "../DynamicVector/dynamicVector.h"

typedef struct Heap Heap;

/* description - takes a Vector and builds a Heap.
output- Pointer to Heap.
errors- NULL pointer to vactor will return NULL */
Heap* HeapBuild(Vector* _vec); /* O(n) */

/* description - frees Heap memmory but keepps the vector.
output- None.
errors- None. */
void HeapDestroy(Heap* _heap);

/* description - Inserts new data to Heap.
output- ADT Errors.
errors- 1. ERR_NOT_INITIALIZED
		2. ERR_OVERFLOW
		3. ERR_REALLOCATION_FAILED
		4. ERR_OK */
ADTErr HeapInsert(Heap* _heap, int _data); /* O(log n) */

/* description - Shows maximun value in Heap.
output- Maximun value or ADT Errors.
errors- 1. ERR_NOT_INITIALIZED
		2. ERR_WRONG_INDEX
		3. ERR_OK */
ADTErr HeapMax(Heap* _heap, int* _data);

/* description - Delete maximum value in Heap and returns it to user.
output- Maximun value or ADT Errors.
errors- 1. ERR_NOT_INITIALIZED
		2. ERR_WRONG_INDEX
		3. ERR_UNDERFLOW
		4. ERR_OK */
ADTErr HeapExtractMax(Heap* _heap, int* _data); /* O(log n) */

/* description - Returns number of items in Heap.
output- Number of items in Heap.
errors- Returns -1 if NULL pointer to vector. */
size_t HeapItemsNum(Heap* _heap);

/* description - Prints out Heap values.
output- None.
errors- None. */
void HeapPrint(Heap* _heap);


#endif /*__HEAP_P__*/
