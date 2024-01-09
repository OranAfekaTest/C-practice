#include "genList.h" 
#include "listInternal.h"
#include <stdlib.h> /* malloc */

List* ListCreate(void)
{
	List* lst = malloc(sizeof(List));
	if(!lst)
	{
		return NULL;
	}
	lst->m_head.m_prev = &(lst->m_head);
	lst->m_head.m_next = &(lst->m_tail);
	lst->m_tail.m_prev = &(lst->m_head);
	lst->m_tail.m_next = &(lst->m_tail);
	return lst;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* itr = NULL;
	Node* temp = NULL;
	if(*_pList)
	{
		itr = (*_pList)->m_head.m_next;
		while(itr->m_next != &((*_pList)->m_tail))
		{
			if(_elementDestroy)
			{
				free(itr->m_data);
			}
			temp = itr->m_next;
			free(itr);
			itr = temp;
		}
		free(*_pList);
	}
}

ListResult ListPushHead(List* _list, void* _item)
{
	Node* nod = NULL;
	if(!_list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(!_item)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	nod = malloc(sizeof(Node));
	if(!nod)
	{
		return LIST_ALLOCATION_ERROR;
	}
	nod->m_data = _item;
	nod->m_next = _list->m_head.m_next;
	nod->m_next->m_prev = nod;
	nod->m_prev = &(_list->m_head);
	_list->m_head.m_next = nod;
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list, void* _item)
{
	Node* nod = NULL;
	if(!_list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(!_item)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	nod = malloc(sizeof(Node));
	if(!nod)
	{
		return LIST_ALLOCATION_ERROR;
	}
	nod->m_data = _item;
	InsertBefore(&(_list->m_tail), nod);
	return LIST_SUCCESS;
}

ListResult ListPopHead(List* _list, void** _pItem)
{
	Node* tmp = NULL;
	if(!_list || !_pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return LIST_EMPTY_ERROR;
	}
	*_pItem = RemoveNode(&(_list->m_head));
	return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem)
{
	Node* tmp = NULL;
	if(!_list || !_pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if(_list->m_tail.m_prev == &(_list->m_head))
	{
		return LIST_EMPTY_ERROR;
	}
	*_pItem = _list->m_tail.m_prev->m_data;
	tmp =_list->m_tail.m_prev->m_prev;
	tmp->m_next = &(_list->m_tail);
	free(_list->m_tail.m_prev);
	_list->m_tail.m_prev = tmp;
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list)
{
	Node* itr = NULL;
	int counter = 0;
	if(!_list || _list->m_head.m_next == &(_list->m_tail))
	{
		return counter;
	}
	itr =  &(_list->m_head);
	while(itr->m_next != &(_list->m_tail))
	{
		counter++;
		itr = itr->m_next;
	}
	return counter;
}

void InsertBefore(Node* _tail, Node* _nod)
{
	_nod->m_next = _tail;
	_tail->m_prev->m_next = _nod;
	_nod->m_prev = _tail->m_prev;
	_tail->m_prev = _nod;
}

void* RemoveNode(Node* _head)
{
	void* data = _head->m_next->m_data;
	Node* tmp = _head->m_next->m_next;
	tmp->m_prev = _head;
	free(_head->m_next);
	_head->m_next = tmp;
	return data;
}

