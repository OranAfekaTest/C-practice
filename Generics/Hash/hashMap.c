#include "hashMap.h"
#include "../List/listFunctions.h"
#include <stdlib.h> /*malloc*/

typedef struct Bucket
{
    void* m_key;
    void* m_value;
}Bucket;

typedef struct Context
{
    void* m_context;
    void* m_elemnet;
    size_t m_counter;
    EqualityFunction m_keysEqualFunc;
    KeyValueActionFunction m_action;
}Context;

struct HashMap
{
    List** m_data;
    size_t m_size;
    size_t m_numOfLists;
    size_t m_numOfBuckets;
    HashFunction m_hashFunc;
    EqualityFunction m_keysEqualFunc;
};

static int IsPrime(size_t _num);
static size_t FindPrimeFrom(size_t _from);
static Bucket* BucketCreate(void* _key, void* _value);
static void BucketDestroy(Bucket** bucket, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
static int ActionAdapter(void* _bucket, void* _context);

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* hashMap = NULL;
    if(_capacity < 1 || !_hashFunc || !_keysEqualFunc)
    {
        return NULL;
    }
    hashMap = malloc(sizeof(HashMap));
    if(!hashMap)
    {
        return NULL;
    }
    hashMap->m_size = FindPrimeFrom(_capacity);
    hashMap->m_data = calloc(sizeof(List*), hashMap->m_size);
    if(!hashMap->m_data)
    {
        free(hashMap);
        return NULL;
    }
    hashMap->m_hashFunc = _hashFunc;
    hashMap->m_keysEqualFunc = _keysEqualFunc;
    hashMap->m_numOfLists = 0;
    hashMap->m_numOfBuckets = 0;
    return hashMap;
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    size_t i;
    ListItr begin, end;
    Bucket *bucket = NULL;
    if(*_map)
    {
        for(i = 0; i < (*_map)->m_numOfLists; i++)
        {
            if((*_map)->m_data[i])
            {
                begin = ListItrBegin((*_map)->m_data[i]);
                end = ListItrEnd((*_map)->m_data[i]);
                while(begin != end)
                {
                    bucket = (Bucket*)ListItrGet(begin);
                    BucketDestroy(&bucket, _keyDestroy, _valDestroy);
                    begin = ListItrNext(begin);
                }
                ListDestroy(&(*_map)->m_data[i], NULL);
            }
        }
        
        free((*_map)->m_data);
        free(*_map);
        *_map = NULL;
    }
}


/** 
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
MapResult HashMapRehash(HashMap *_map, size_t newCapacity);

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
    size_t index;
    if(!_map)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_key)
    {
        return MAP_KEY_NULL_ERROR;
    }
    index = _map->m_hashFunc(_key) % _map->m_size;
    if(!_map->m_data[index])
    {
        _map->m_data[index] = ListCreate();
        if(!_map->m_data[index])
        {
            return MAP_ALLOCATION_ERROR;
        }
        _map->m_numOfLists++;
    }
    else
    {
        if(ListItrEnd(_map->m_data[index]) != ListItrFindFirst(ListItrBegin(_map->m_data[index]), ListItrEnd(_map->m_data[index]), _map->m_keysEqualFunc, _key))
        {
            return MAP_KEY_DUPLICATE_ERROR;
        }
        
    }
    ListPushHead(_map->m_data[index], BucketCreate(_key, _value));
    _map->m_numOfBuckets++;
    return MAP_SUCCESS;
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t index;
    ListItr listItr = NULL;
    Bucket* bucket = NULL;
    if(!_map || !_pValue)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_searchKey)
    {
        return MAP_KEY_NULL_ERROR;
    }
    index = _map->m_hashFunc(_searchKey) % _map->m_size;
    if(!_map->m_data[index])
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    listItr = ListItrFindFirst(ListItrBegin(_map->m_data[index]), ListItrEnd(_map->m_data[index]), _map->m_keysEqualFunc, _searchKey);
    if(ListItrEnd(_map->m_data[index]) == listItr)
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    bucket = (Bucket*)ListItrRemove(listItr);
    if(!bucket)
    {
        return MAP_GENERAL_ERROR;
    }
    *_pKey = bucket->m_key;
    *_pValue = bucket->m_value;
    _map->m_numOfBuckets--;
    return MAP_SUCCESS;
}

MapResult HashMapFind(const HashMap* _map, const void* _key, void** _pValue)
{
    size_t index;
    ListItr listItr = NULL;
    Bucket* bucket = NULL;
    if(!_map || !_pValue)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(!_key)
    {
        return MAP_KEY_NULL_ERROR;
    }
    index = _map->m_hashFunc(_key) % _map->m_size;
    if(!_map->m_data[index])
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    listItr = ListItrFindFirst(ListItrBegin(_map->m_data[index]), ListItrEnd(_map->m_data[index]), _map->m_keysEqualFunc, _key);
    if(ListItrEnd(_map->m_data[index]) == listItr)
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    bucket = (Bucket*)ListItrGet(listItr);
    if(!bucket)
    {
        return MAP_GENERAL_ERROR;
    }
    *_pValue = bucket->m_value;
    return MAP_SUCCESS;
}


size_t HashMapSize(const HashMap* _map)
{
    if(!_map)
    {
        return -1;
    }
    return _map->m_numOfBuckets;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t i;
    ListItr begin, end;
    Bucket* bucket = NULL;
    Context context;
    if(!_map || !_action)
    {
        return 0;
    }
    for(i = 0; i < _map->m_size; i++)
    {
        if(_map->m_data[i])
        {
            begin = ListItrBegin(_map->m_data[i]);
            end = ListItrEnd(_map->m_data[i]);
            context.m_action = _action;
            context.m_counter = 0;
            context.m_context = _context;
            if(ListItrForEach(begin, end, ActionAdapter, (void*)&context) != end)
            {
                break;
            }
        }
    }

    return context.m_counter;
}

/*
MapStats HashMapGetStatistics(const HashMap* _map)
{
    if(!_map)
    {
        return NULL;
    }
    return _map->m_stats;
}
*/

int IsPrime(size_t _num)
{
    size_t i, result;
    for(i = 2; i < _num; i++)
    {
        if(_num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

size_t FindPrimeFrom(size_t _from)
{
    while(!IsPrime(++_from));
    return _from;
}

Bucket* BucketCreate(void* _key, void* _value)
{
    Bucket* bucket = NULL;
    if(!_key)
    {
        return NULL;
    }
    bucket = malloc(sizeof(Bucket));
    if(!bucket)
    {
        return NULL;
    }
    bucket->m_key = _key;
    bucket->m_value = _value;
    return bucket;
}

void BucketDestroy(Bucket** bucket, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    if(*bucket)
    {
        if(_keyDestroy)
        {
            _keyDestroy((*bucket)->m_key);
        }
        if(_valDestroy)
        {
            _valDestroy((*bucket)->m_value);
        }
        free(*bucket);
        *bucket = NULL;
    }
}

int ActionAdapter(void* _bucket, void* _context)
{
    ((Context*)_context)->m_counter++;
    return ((Context*)_context)->m_action(((Bucket*)_bucket)->m_key, ((Bucket*)_bucket)->m_value, ((Context*)_context)->m_context);
}
