#ifndef __HASHSET_H__
#define __HASHSET_H__
#include <stddef.h>

typedef enum HashSet_Result
{
    SET_SUCCESS = 0,
    SET_UNINITIALIZED, /** Uninitialized HasSeterror*/
    SET_KEY_DUPLICATE, /** Duplicate key error */
    SET_KEY_NOT_FOUND, /** Key not found */
    SET_OVERFLOW /**No more space in HashSet */
} HashSet_Result;

typedef struct Hash Hash;
typedef size_t (*HashFunction)(void* _data);
typedef int (*EqualityFunction)(void* _firstData, void* _secondData);

/**  
 * @brief Dynamically create a new hash  
 * @param[in] _size - size of hash to allocate, wil be greater by a factor
 * @param[in] _hashFunction - function to hash the inserted data 
 * @param[in] _equalityFunction - function to compare the inserted data 
 * @return Hash * - on success
 * @retval NULL on fail 
 */
Hash* HashCreate(size_t _size, HashFunction _hashFunction, EqualityFunction _equalityFunction);
/**  
 * @brief Deallocate a previously allocated hash
 * @param[in] _heap - Heap to be deallocated.  On success will be nulled.
 * @param[in] _keyDestroy - destroyer function for the type of data in the hash.
 */
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data));
/**  
 * @brief Add an element to the HashSet.  
 * @param[in] _hash - HashSet to insert element to.
 * @param[in] _data - Element to insert.
 * @return success or error code 
 * @retval SET_SUCCESS  on success
 * @retval SET_UNINITIALIZED  error, heap or data not initilized
 * @retval SET_KEY_DUPLICATE error, data already exist in hashset 
 */
HashSet_Result HashInsert(Hash* _hash, void* _data);
/**  
 * @brief Remove an element to the HashSet.  
 * @param[in] _hash - HashSet to remove element to.
 * @param[in] _key - Element to remove.
 * @param[out] _data - the data removed
 * @return success or error code 
 * @retval SET_SUCCESS  on success
 * @retval SET_UNINITIALIZED  error, heap or data not initilized
 * @retval SET_KEY_NOT_FOUND error, data already exist in hashset 
 */
HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data);

int HashIsFound(const Hash* _hash, void* _key);

size_t HashNumOfItems(const Hash* _hash);

size_t HashCapacity(const Hash* _hash);

double HashAverageRehashes(const Hash* _hash);

size_t HashMaxReHash(const Hash* _hash);

void HashPrint(const Hash* _hash, void (*PrintKey)(void*));

void HanldleHashSetResult(HashSet_Result result, char* msg)

#endif /* __HASHSET_H__ */
