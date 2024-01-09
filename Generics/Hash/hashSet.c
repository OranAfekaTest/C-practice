#include "hashSet.h"
#include <stdlib.h>
#define FACTOR 1.3

struct Hash
{
    void** m_data;
    char* m_state;
    HashFunction m_hashFunction);
    EqualityFunction m_equalityFunction;
    size_t m_hashSize; /*original size given by the client*/
    size_t m_capacity; /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
    size_t m_maxOfRehashOperations; /*maximum amount of rehash operations
    which have been done over one insertion*/
    size_t m_counterOfInsertions; /*total amount of insertions into the table*/
    size_t m_allRehashOperations; /*all rehash operations mutual counter*/
};

const char* HashSetResult[] = 
{
    "Success",
    "Uninitialized HasSeterror",
    "Duplicate key error",
    "Key not found",
    "No more space in HashSet"
};

static size_t ReHash(size_t _key);
static size_t FindPrimeFrom(size_t _from);
static int IsPrime(size_t _num);

Hash* HashCreate(size_t _size, HashFunction _hashFunction, EqualityFunction _equalityFunction)
{
    Hash* hash = NULL;
    if(_size < 1 || !_hashFunction || !_equalityFunction)
    {
        return NULL;
    }
    hash = malloc(_size * sizeof(Hash));
    if(!hash)
    {
        return NULL;
    }
    hash->m_data = calloc(sizeof(void**), _size);
    if(!hash->m_data)
    {
        free(hash);
        return NULL;
    }
    hash->m_state = calloc(sizeof(char*), _size);
    if(!hash->m_state)
    {
        free(hash->m_data);
        free(hash);
        return NULL;
    }
     
    hash->m_hashFunction = _hashFunction;
    hash->m_equalityFunction = _equalityFunction;
    hash->m_hashSize = _size;
    hash->m_capacity = FindPrimeFrom(_size * FACTOR);
    hash->m_numOfItems = 0;
    hash->m_maxOfRehashOperations = 0;
    hash->m_counterOfInsertions = 0;
    hash->m_allRehashOperations = 0; 
    return hash;
}

void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
    size_t i;
    if(*_hash)
    {
        if(_keyDestroy)
        {
            for(i = 0; i < (*_hash)->m_capacity; i++)
            {
                if((*_hash)->m_state == 2)
                {
                    _keyDestroy((*_hash)->m_data[i]);
                }
            }
        }
        free((*_hash)->m_data);
        free((*_hash)->m_state);
        free(*_hash);
        *_hash = NULL;
    }
}

HashSet_Result HashInsert(Hash* _hash, void* _data)
{
    size_t i, key, rehashCounter = 0;
    if(!_hash || !_data)
    {
        return SET_UNINITIALIZED;
    }
    if(_hash->m_capacity <= _hash->m_numOfItems)
    {
        return SET_OVERFLOW;
    }
    for(i = 0; i < (*_hash)->m_capacity; i++)
    {
        if((*_hash)->m_state == 2)
        {
            if(_hash->m_equalityFunction(_data, _hash->m_data[i]))
            {
                return SET_KEY_DUPLICATE;
            }
        }
    }

    key = _hash->m_hashFunction(_data) % _hash->m_capacity;
    while(_hash->m_state[key] == 2)
    {
        key = ReHash(key) % (*_hash)->m_capacity;
        hash->m_allRehashOperations++;
        rehashCounter++;  
    }
    if(_hash->m_maxOfRehashOperations < rehashCounter)
    {
        _hash->m_maxOfRehashOperations = rehashCounter;
    }
    _hash->m_data[key] = _data;
    _hash->m_counterOfInsertions++;
    _hash->m_numOfItems;
    _hash->m_state[key] = 2;
    return SET_SUCCESS;
}

HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
    size_t key, i;
    if(!_hash || _key || _data)
    {
        return SET_UNINITIALIZED;
    }
    key = _hash->m_hashFunction(_key);
    for(i = 0; i < _hash->m_maxOfRehashOperations; i++)
    {
        if(_hash->m_equalityFunction(_key, _hash->m_data[key]))
        {
            break;
        }
        key = ReHash(key) % _hash->m_capacity;
    }
    if(i == _hash->m_maxOfRehashOperations)
    {
        return SET_KEY_NOT_FOUND;
    }
    *_data = _hash->m_data[key];
    _hash->m_numOfItems--;
    _hash->m_state[key] = 1;
    
    return SET_SUCCESS;
}

int HashIsFound(const Hash* _hash, void* _key)
{
    if(_hash->m_maxOfRehashOperations < rehashCounter)
        {
            return ;
        }
}

size_t HashNumOfItems(const Hash* _hash)
{
    if(!_hash)
    {
        return 0;
    }
    return  _hash->m_numOfItems;
}

size_t HashCapacity(const Hash* _hash)
{
    if(!_hash)
    {
        return 0;
    }
    return _hash->m_capacity;
}

double HashAverageRehashes(const Hash* _hash)
{
    if(!_hash || !_hash->m_counterOfInsertions)
    {
        return 0;
    }
    return _hash->m_allRehashOperations / hash->m_counterOfInsertions;
}

size_t HashMaxReHash(const Hash* _hash)
{
    if(!_hash)
    {
        return 0;
    }
    return _hash->m_maxOfRehashOperations;
}

void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
    size_t i;
    if(!_hash || !PrintKey)
    {
        return;
    }
    for(i = 0; i < _hash->m_capacity; ++i)
    {
        if(_hash->m_state[i] == 2)
        {
            PrintKey(_hash->m_data[i]);
        }
    }
}

void HanldleHashSetResult(HashSet_Result result, char* msg)
{
    if(result)
    {
        printf("%s, %s.\n", HashSetResult[result], msg);
    }
}


size_t ReHash(size_t _key)
{
    return _key + 1;
}

int IsPrime(size_t _num)
{
    size_t i, result;
    for(i = 2; i < _num; i++)
    {
        if(_num % i == 0)
        {
            return 0
        }
    }
    return 1;
}

size_t FindPrimeFrom(size_t _from)
{
    while(!IsPrime(++_from));
    return _from;
}