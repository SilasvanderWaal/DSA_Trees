//=============================================================================
// bst.c - binary search tree, based on binary tree (bt.h/bt.c)
//=============================================================================
#include "../include/global.h"
#include "../include/bst.h"

//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a);
static void _inorder(BST T, int* pos, int* a);
//-----------------------------------------------------------------------------
// public functions, exported through bst.h
//-----------------------------------------------------------------------------
// new_BST: creates a new BST
BST new_BST(int val)
{
	return new_BT(val);
}
//-----------------------------------------------------------------------------
// bst_add: adds the value v to the BST T (unless duplicate)
//-----------------------------------------------------------------------------
BST bst_add(BST T, int v)
{
	return	!T            	?	new_BST(v)                            :
		v < get_val(T)	?	cons(add(get_LC(T), v), T, get_RC(T)) :
		v > get_val(T)	?	cons(get_LC(T), T, add(get_RC(T), v)) :
		/* duplicate */		T;
}
//-----------------------------------------------------------------------------
// bst_rem: removes the value val from the BST (if it exists)
//-----------------------------------------------------------------------------
BST bst_rem(BST T, int val)
{
	// TODO
	return T;
}
//-----------------------------------------------------------------------------
// preorder: puts the BST T values into array a in preorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void preorder(BST T, int* a)
{
	int pos = 0;
	_preorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// inorder: puts the BST T values into array a in inorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,2,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void inorder(BST T, int* a)
{
    int pos = 0;
    _inorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// postorder: puts the BST T values into array a in postorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,3,2]      / \  --> [3,2]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void postorder(BST T, int* a)
{
	// TODO
}
//-----------------------------------------------------------------------------
// bfs: puts the BST T values into array a in bfs-order, non-nodes
// are indicated by X, as defined in global.h
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,X,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void bfs(BST T, int* a, int max)
{
    if (max < 0) { return; }
    if (T == NULL) { *a = X; return; }
    *a = T->val;
    bfs(T->LC, a + 1, max - 1);
    bfs(T->RC, a + 1, max - 1);
}
//-----------------------------------------------------------------------------
// is_member: checks if value val is member of BST T
//-----------------------------------------------------------------------------
bool is_member(BST T, int val)
{
    if(!T){return false;}

    if(get_val(T) == val)
        return true;

    if(val < get_val(T))
        return is_member(get_LC(T), val);

    return is_member(get_RC(T), val);
}
//-----------------------------------------------------------------------------
// height: returns height of BST T
//-----------------------------------------------------------------------------
int height(BST T)
{
    if(!T){return 0;}

    int left = height(get_LC(T));
    int right = height(get_RC(T));

	return (left > right ? left : right) + 1;
}
//-----------------------------------------------------------------------------
// size: returns size of BST T
//-----------------------------------------------------------------------------
int size(BST T)
{
	if(!T){return 0;}

	int left = size(get_LC(T));
	int right = size(get_RC(T));

	return left + right + 1;
}
//-----------------------------------------------------------------------------
// private helper functions, not exported
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a)
{
	if (T)
	{
		a[(*pos)++] = get_val(T);
		_preorder(get_LC(T), pos, a);
		_preorder(get_RC(T), pos, a);
	}
}

static void _inorder(BST T, int* pos, int* a){
    if(!T){return;}
	_preorder(get_LC(T), pos, a);
	a[(*pos)++] = get_val(T);
	_preorder(get_RC(T), pos, a);
}
