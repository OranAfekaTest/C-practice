#include "linkedPerson.h"


Person* ListInsertHead(Person* _head ,Person* _p)
{
	if(!_p)
	{
		return _head; /* can't insert null */
	}
	_p->m_next = _head;
	return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
	if(!_head || !_item)
	{
		return _head;
	}
	*_item = _head;
	_head = _head->m_next;
	return _head;
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	Person* itr= NULL;
	if(!_head) /* empty list */
	{
		_head = _p;
		return _p;
	}
	
	if(_p->m_id < _head->m_id)
	{
		return ListInsertHead(_head, _p);
	}
	if(!(_head->m_next)) /* single node list */
	{
		_head->m_next = _p;
		return _head;
	}
	itr = _head->m_next;
	while(itr->m_next);
	{
		if(_p->m_id < itr->m_next->m_id)
		{
			_p->m_next = itr->m_next;
			itr->m_next = _p;
			return _head;
		}
		itr = itr->m_next;
	}
	itr->m_next = _p;
	return _head;
}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if(!_head)
	{
		_head = _p;
		return _head;
	}
	if(_p->m_id < _head->m_id)
	{
		_p->m_next = _head;
		_head = _p;
		return _head;
	}
	_head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
	return _head;
}

Person* ListRemoveByKey(Person* _head, int _key, Person* *_p)
{
	Person* itr= NULL;
	if(!_head)
	{
		return _head;
	}
	if(_head->m_id == _key)
	{
		*_p = _head;
		return _head;
	}
	itr = _head->m_next;
	while(itr->m_next)
	{
		if(itr->m_next->m_id == _key)
		{
			*_p = itr->m_next;
			itr->m_next =  itr->m_next->m_next;
			return _head;
		}
	}
	return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p)
{
	if(!_head)
	{
		return _head;
	}
	if(_head->m_next->m_id == _key)
	{
		*_p = _head->m_next;
		_head->m_next = _head->m_next->m_next;
		return _head;
	}
	ListRemoveByKeyRec(_head->m_next, _key, _p);
	return _head;
}

Person* LastNodeRec(Person* _head)
{
	if(!_head)
	{
		return _head;
	}
	if(!(_head->m_next))
	{
		return _head;
	}
	LastNodeRec(_head->m_next);
}

Person* OldestPersonRec(Person* _head)
{
	if(!(_head->m_next) || !_head)
	{
		return _head;
	}
	return (_head->m_age < OldestPersonRec(_head->m_next)->m_age ? OldestPersonRec(_head->m_next) : _head);
}

void PrintList(Person* _head)
{
	if(!_head)
	{
		return;
	}
	printf("%s age:%d, ID:%d\n", _head->m_name, _head->m_age, _head->m_id);
	PrintList(_head->m_next);
}
