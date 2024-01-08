#ifndef __DYNAMICVECTOR_H__
#define __DYNAMICVECTOR_H__
#include <stdlib.h>
#include "ADTDef.h"

typedef struct Vector Vector;

/* size - The initial allocation size.
blockSize - The extention block size. */
Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize);
void VectorDestroy(Vector** _vector);
ADTErr VectorAdd(Vector *_vector, int _item); /* Add item to end. */
ADTErr VectorDelete(Vector *_vector, int* _item); /* Delete item from the end. */

/* The Index range in the following functions is : 0..numOfItems-1 */
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);
ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems);

/* Unit-Test functions */
void VectorPrint(Vector *_vector);
int* VectorGetItems(Vector *_vector);
size_t VectorGetOriginalSize(Vector *_vector); /* original allocated space for items */
size_t VectorGetSize(Vector *_vector); /* actual allocated space for items*/
size_t VectorGetNumOfItems(Vector *_vector); /* actual number of items */
size_t VectorGetBlockSize(Vector *_vector); /* the chunk size to be allocated when no space*/


#endif /*__DYNAMICVECTOR_H__*/
