#include "myMalloc.h"


void MyMallocInit(void* _memory, size_t _memorySize)
{
    if(!_memory || !_memorySize)
    {
        return;
    }
    *(size_t*)_memory = _memorySize;
    *((size_t*)(_memory) + 1) = _memorySize - sizeof(_memorySize);
    *((size_t*)(_memory) + _memorySize/sizeof(_memorySize) - 1) = 0;
}
/*Every allocation returns _requiredBlockSize bytes to the client,
* but reserves _requiredBlockSize+8 bytes from _memory . */
void* MyMalloc(void* _memory, size_t _requiredBlockSize)
{

}
void MyFree(void* _myBlock)
{

}