#include "binaryTree.h"

void NodeDestroy(Node* _node);
Node* CreateNode(Node* _father, int _data);
ADTErr InsertToNode(Node* _node, int _data);
int IsDataInNode(Node* _node, int _data);
void PrePrint(Node* _node);
void InPrint(Node* _node);
void PostPrint(Node* _node);
typedef struct Node Node;
struct Node
{
	int m_data;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

struct Tree
{
	Node* m_root;
};

Tree* TreeCreate()
{
	Tree* tree = malloc(sizeof(Tree));
	return tree;
}

void TreeDestroy(Tree* _tree)
{
	if(_tree->m_root)
	{
		NodeDestroy(_tree->m_root);
	}
	free(_tree);
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	if(!_tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return InsertToNode(_tree->m_root, _data, NULL);
}

int TreeIsDataFound(Tree* _tree, int _data)
{
	if(!_tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	return IsDataInNode(_tree->m_root, _data);
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(!_tree)
	{
		return;
	}
	switch(_traverseMode)
	{
		case PRE_ORDER:
			printf("Pre order Tree print: ");
			PrePrint(_tree->m_root);
			break;
		
		case IN_ORDER:
			printf("In order Tree print: ");
			InPrint(_tree->m_root);
			break:
			
		case POST_ORDER:
			printf("Post order Tree print: ");
			PostPrint(_tree->m_root);
			break:
	}
}

void NodeDestroy(Node* _node)
{
	if(m_left)
	{
		NodeDestroy(m_left);
	}
	if(m_right)
	{
		NodeDestroy(m_right);
	}
	free(_node);
}

Node* CreateNode(Node* _father, int _data)
{
	Node* nod = malloc(sizeof(Node));
	if(!nod)
	{
		return NULL;
	}
	nod->m_data = _data;
	nod->m_father = _father;
	nod->m_right = NULL;
	nod->m_left = NULL;
	return nod;
}

ADTErr InsertToNode(Node* _node, int _data, Node* _father)
{
	if(!_node)
	{
		_node = CreateNode(_father, _data);
		if(_node)
		{
			return ERR_OK;
		}
		else
		{
			return ERR_ALLOCATION_FAILED;
		}
	}
	if(_node->m_data < _data)
	{
		return InsertToNode(_node->m_right, _data, _father);
	}
	else if(_data < _node->m_data)
	{
		return InsertToNode(_node->m_left, _data, _father);
	}
	else
	{
		return ERR_DATA_EXIST;
	}
}

int IsDataInNode(Node* _node, int _data)
{
	if(!_node)
	{
		return 0;
	}
	if(_node->m_data < _data)
	{
		return InsertToNode(_node->m_right, _data);
	}
	else if(_data < _node->m_data)
	{
		return InsertToNode(_node->m_left, _data);
	}
	else
	{
		return 1;
	}
}

void PrePrint(Node* _node)
{
	if(!_node)
	{
		return;
	}
	printf("%d, ", _node->m_data);
	PrePrint(_node->m_left);
	PrePrint(_node->m_right);
}

void InPrint(Node* _node)
{
	if(!_node)
	{
		return;
	}
	PrePrint(_node->m_left);
	printf("%d, ", _node->m_data);
	PrePrint(_node->m_right);
}
void PostPrint(Node* _node)
{
	if(!_node)
	{
		return;
	}
	PrePrint(_node->m_left);
	PrePrint(_node->m_right);
	printf("%d, ", _node->m_data);
}
