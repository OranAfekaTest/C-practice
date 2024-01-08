#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__



typedef struct Tree Tree;

typedef enum
{
PRE_ORDER,
IN_ORDER,
POST_ORDER
} TreeTraverse;

Tree* TreeCreate();

void TreeDestroy(Tree* _tree);

ADTErr TreeInsert(Tree* _tree, int _data);

int TreeIsDataFound(Tree* _tree, int _data);

void TreePrint(Tree* _tree, TreeTraverse _traverseMode);

#endif /* __BINARY_TREE_H__ */
