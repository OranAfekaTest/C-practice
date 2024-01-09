#ifndef __LISTINTR_H__
#define __LISTINTR_H__
#include <stdlib.h> /* free */

typedef struct Node Node;
struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
};

void InsertBefore(Node* _tail, Node* _nod);
void* RemoveNode(Node* _head);

#endif /* __LISTINTR_H__ */

