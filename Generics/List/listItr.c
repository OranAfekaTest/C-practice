#include "listItr.h"
#include "listInternal.h"
#define LIST_ITR_EQUALS(_a, _b) _a == _b

ListItr ListItrBegin(const List* _list)
{
	if(!_list)
	{
		return NULL;
	}
	return (ListItr)_list->m_head.m_next;
}

ListItr ListItrEnd(const List* _list)
{
	if(!_list)
	{
		return NULL;
	}
	return (ListItr)&_list->m_tail;
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
	return _a == _b;
}

ListItr ListItrNext(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return (ListItr)((Node*)_itr)->m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return (ListItr)((Node*)_itr)->m_prev;
}

void* ListItrGet(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	if(((Node*)_itr)->m_next == _itr)
	{
		return NULL;
	}
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void* data;
	if(!_itr || !_element)
	{
		return NULL;
	}
	data = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	return data;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	if(!_itr || !_element)
	{
		return NULL;
	}
	InsertBefore((Node*)_itr, (Node*)_element);
	return (ListItr*)_element;
}

void* ListItrRemove(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return RemoveNode(((Node*)_itr)->m_prev);
}
