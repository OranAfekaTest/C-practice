#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdio.h>

typedef struct Person Person;
struct Person
{
	int m_id; /* Primary Key */
	char m_name[128];
	int m_age;
	Person* m_next;
};

Person* ListInsertHead(Person* _head ,Person* _p);

Person* ListRemoveHead(Person* _head, Person** _item);

Person* ListInsertByKey(Person* _head, int _key, Person* _p);

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);

Person* ListRemoveByKey(Person* _head, int _key, Person* *_p);

Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);

Person* LastNodeRec(Person* _head);

Person* OldestPersonRec(Person* _head);

void PrintList(Person* _head);

#endif /* __LINKEDLIST_H__ */
