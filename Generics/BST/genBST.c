#include "genBST.h"
#include <stdlib.h> /*malloc*/
#define I_AM_RIGHT_CHILD(node) node == node->m_father->m_right
#define I_AM_LEFT_CHILD(node) node == node->m_father->m_left
#define END &_tree->m_sentinal

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_left;
	Node* m_right;
    Node* m_father;
};

struct BSTree
{
    Node m_sentinal;
    LessComparator m_less;
};


static void FreeNode(Node* _nod, void (*_destroyer)(void*));
static Node* CreateNode(Node* _father, void* _data);
static Node* InsertToNode(Node* _node, void* _data, Node* _father, LessComparator _less);
static Node* BeginNode(Node* _node);

BSTree* BSTreeCreate(LessComparator _less)
{
    BSTree* tree;
    if(!_less)
    {
        return NULL;
    }
    tree = malloc(sizeof(BSTree));
    if(!tree)
    {
        return NULL;
    }
    tree->m_less = _less;
    tree->m_sentinal.m_data = NULL;
    tree->m_sentinal.m_father = &tree->m_sentinal;
    tree->m_sentinal.m_left = &tree->m_sentinal;
    tree->m_sentinal.m_right = NULL;
	return tree;
}

void  BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*))
{
    if(_tree)
    {
        FreeNode((*_tree)->m_sentinal.m_left, _destroyer);
        free(*_tree);
        *_tree = NULL;
    }
}

BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
    BSTreeItr result;
    if(!_tree || !_item)
    {
        NULL;
    }
    result = (BSTreeItr)InsertToNode(_tree->m_sentinal.m_left, _item, END, _tree->m_less);
    if(!result)
    {
        result = (BSTreeItr)END;
    }
    return result;
}

/** 
 * @brief Search the first element for which the given predicate returns 0
 * iterating using in-order manner over elements
 * O(k * n) where O(k) is the time complexity of the predicate
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _predicate : Predicate function
 * @param _params : Predicate parameters
 * @return an iterator pointing to the first data found, to end of tree if not found or NULL on NULL input
 */
BSTreeItr BSTreeFindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context);

BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
    BSTreeItr result;
    if(!_tree)
    {
        NULL;
    }
    if(_tree->m_sentinal.m_left == END)
    {
        result = (BSTreeItr*)_tree->m_sentinal.m_left;
    }
    else
    {
        result = (BSTreeItr*)BeginNode(_tree->m_sentinal.m_left);
    }
    return result;
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
    if(!_tree)
    {
        NULL;
    }
    return (BSTreeItr*)END;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    return _a == _b;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    BSTreeItr result = NULL;
    Node* node = (Node*) _it;
    if(_it)
    {
        if(node->m_right)
        {
            node = BeginNode(node->m_right);
        }
        else if(I_AM_RIGHT_CHILD(node))
        {
            while(I_AM_RIGHT_CHILD(node))
            {
                node = node->m_father;
            }
            node = node->m_father;
        }
        else
        {
            node = node->m_father;
        }
        result = (BSTreeItr)node;
    }
    return result;
}

/** 
 * @brief Get itertator to the previous element from current iterator
 *
 * @param _it : A tree iterator
 * @return an iterator pointing at the previous element
 * or to the beginning if _it points to the beginning
 */
BSTreeItr BSTreeItrPrev(BSTreeItr _it);

/** 
 * @brief Removes element from tree
 * @details Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param _it : A tree iterator
 * @return removed item or null on failure
 */
void* BSTreeItrRemove(BSTreeItr _it);

/** 
 * @brief Get element pointed to by iterator from tree
 * Average/Worst time complexity O(1).
 *
 * @param _it : A tree iterator
 * @return the item the iterator points at or null if _it as at end
 */
void* BSTreeItrGet(BSTreeItr _it)
{
    Node* node = (Node*)_it;
    if(!node || node == node->m_father)
    {
        return NULL;
    }
    return node->m_data;
}

/** 
 * @brief Performs an action function on every element in tree, by given traversal mode
 * @details iteration will on the first element for which action returns a zero
 * or on reaching end of the conrainer
 *
 * @params _tree : tree to iterate over
 * @params _mode : Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @params _action : Action function to call for each element
 * @params _context : Parameters for the function
 * @return Iterator to end or an iterator to the specific element where action returned none zero value
 */
BSTreeItr BSTreeForEach(const BSTree* _tree, BSTreeTraversalMode _mode, ActionFunction _action, void* _context);

void FreeNode(Node* _nod, void (*_destroyer)(void*))
{
    if(!_nod)
    {
        return;
    }
    FreeNode(_nod->m_left, _destroyer);
    FreeNode(_nod->m_right, _destroyer);
    if(_destroyer)
    {
         _destroyer(_nod->m_data);
    }
    free(_nod);
}

Node* InsertToNode(Node* _node, void* _data, Node* _father, LessComparator _less)
{
    if(!_node)
	{
		_node = CreateNode(_father, _data);
		return _node;
	}
	if(_less(_node->m_data, _data))
	{
		return InsertToNode(_node->m_right, _data, _father, _less);
	}
	else if(_less(_data, _node->m_data))
	{
		return InsertToNode(_node->m_left, _data, _father, _less);
	}
	else
	{
		return NULL;
	}
}

Node* CreateNode(Node* _father, void* _data)
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

Node* BeginNode(Node* _node)
{
    if(!_node->m_left)
    {
        return _node;
    }
    return BeginNode(_node->m_left);
}