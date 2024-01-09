#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#define MAGIC_NUMBER 31689

typedef struct Node Node;
struct Node
{
	int m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
};

List* ListCreate(void)
{
	List* lst = malloc(sizeof(List));
	lst->m_head.m_prev = NULL;
	lst->m_head.m_next = &(lst->m_tail);
	lst->m_tail.m_prev = &(lst->m_head);
	lst->m_tail.m_next = NULL;
	lst->m_tail.m_data = MAGIC_NUMBER;
	return lst;
}

void ListDestroy(List* _list)
{
	Node* itr = NULL;
	Node* temp = NULL;
	if(!_list)
	{
		return;
	}
	if(_list->m_tail.m_data == MAGIC_NUMBER)
	{
		_list->m_tail.m_data = 0;
		itr = _list->m_head.m_next;
		while(itr->m_next != &(_list->m_tail))
		{
			temp = itr->m_next;
			free(itr);
			itr = temp;
		}
		free(_list);
	}
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* nod = NULL;
	if(!_list)
	{
		return ERR_NOT_INITIALIZED;
	}
	nod = malloc(sizeof(Node));
	nod->m_data = _data;
	nod->m_next = _list->m_head.m_next;
	nod->m_next->m_prev = nod;
	nod->m_prev = &(_list->m_head);
	_list->m_head.m_next = nod;
	return ERR_OK;
}

ADTErr ListPushTail(List* _list, int _data)
{
	Node* nod = NULL;
	if(!_list)
	{
		return ERR_NOT_INITIALIZED;
	}
	nod = malloc(sizeof(Node));
	nod->m_data = _data;
	nod->m_next = &(_list->m_tail);
	_list->m_tail.m_prev->m_next = nod;
	nod->m_prev = _list->m_tail.m_prev;
	_list->m_tail.m_prev = nod;
	return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data)
{
	Node* tmp = NULL;
	if(!_list || !_data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_EMPTY_LIST;
	}
	*_data = _list->m_head.m_next->m_data;
	tmp =_list->m_head.m_next->m_next;
	tmp->m_prev = &(_list->m_head);
	free(_list->m_head.m_next);
	_list->m_head.m_next = tmp;
	return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{
	Node* tmp = NULL;
	if(!_list || !_data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_tail.m_prev == &(_list->m_head))
	{
		return ERR_EMPTY_LIST;
	}
	*_data = _list->m_tail.m_prev->m_data;
	tmp =_list->m_tail.m_prev->m_prev;
	tmp->m_next = &(_list->m_tail);
	free(_list->m_tail.m_prev);
	_list->m_tail.m_prev = tmp;
	return ERR_OK;
}

size_t ListCountItems(List* _list)
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

int ListIsEmpty(List* _list)
{
	if(!_list || _list->m_head.m_next == &(_list->m_tail))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* ListPrint is only for debug */

void ListPrint(List* _list)
{
	Node* itr = NULL;
	if(!_list)
	{
		return;
	}
	itr = _list->m_head.m_next;
	printf("head->");
	while(itr != &(_list->m_tail))
	{
		printf("%d->", itr->m_data);
		itr = itr->m_next;
	}
	printf("tail.\n");
}
