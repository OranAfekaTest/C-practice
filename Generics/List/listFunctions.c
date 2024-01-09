#include "listFunctions.h"

typedef int (*InnerFunction)(int _result, void* _context);


static int InnerFindFirst(int _result, void* _context);
static int InnerCountIf(int _result, void* _context);
static int InnerForEach(int _result, void* _context);
static ListItr ListItrEngine(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context, InnerFunction _inner, void* _InnerContext);

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    if(!_begin || !_end || !_predicate)
    {
        return NULL;
    }
    ListItrEngine(_begin, _end, _predicate, _context, InnerFindFirst, NULL);
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    size_t result;
    if(!_begin || !_end || !_predicate)
    {
        return -1;
    }
    ListItrEngine(_begin, _end, _predicate, _context, InnerCountIf, (void*)&result);
    return result;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    if(!_begin || !_end || !_action)
    {
        return NULL;
    }
    ListItrEngine(_begin, _end, _action, _context, InnerForEach, NULL);
}

int InnerFindFirst(int _result, void* _context)
{
    return _result;
}

int InnerCountIf(int _result, void* _context)
{
    static size_t counter = 0;
    counter++;
    *(size_t*)_context = counter;
    return 1;
}

int InnerForEach(int _result, void* _context)
{
    return _result;
}

ListItr ListItrEngine(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context, InnerFunction _inner, void* _InnerContext)
{
    ListItr data;
    int result;
    while (_begin != _end)
    {
        data = ListItrGet(_begin);
        result = _predicate(data, _context);
        result = _inner(result, _InnerContext);
        if(!result)
        {
            break;
        }
        _begin = ListItrNext(_begin);
    }
    return _begin;
}
