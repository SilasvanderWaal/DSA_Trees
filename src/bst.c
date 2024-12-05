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
static void _bfs(BST T, int *a, int pos, int max);
static BST _find_successor(BST T);
static BST _find_predeccessor(BST T);
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
    //Base case, NULL
    if(!T){return T;}

    //Searching for the key in the tree
    if(val < get_val(T))
        set_LC(T, bst_rem(get_LC(T), val));
    else if(val > get_val(T))
        set_RC(T, bst_rem(get_RC(T), val));
    else{
        //Key is found
        //No child or right child
        if(!get_LC(T)){
            BST temp = get_RC(T);
            free(T);
            return temp;
        }

        //Left child
        if(!get_RC(T)){
            BST temp = get_LC(T);
            free(T);
            return temp;
        }

        //Two children
        BST replacement_node;
        int left_height = height(get_LC(T));
        int right_height = height(get_RC(T));
        replacement_node = left_height >= right_height ? _find_predeccessor(T) : _find_successor(T);

        set_val(T, get_val(replacement_node));

        if(left_height >= right_height)
            set_LC(T, bst_rem(get_LC(T), get_val(replacement_node)));
        else
            set_RC(T, bst_rem(get_RC(T), get_val(replacement_node)));

    }
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
//       5                    2
//      / \	--> [2,1,3]      / \  --> [2,X,3]
//     4   *
//   3   * x  x              *  3
//-----------------------------------------------------------------------------
void bfs(BST T, int* a, int max)
{
    _bfs(T, a, 0, max);
    return;
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
	_inorder(get_LC(T), pos, a);
	a[(*pos)++] = get_val(T);
	_inorder(get_RC(T), pos, a);
}

//Next node in the inorder travers
static BST _find_successor(BST T){
    //Entering right child, please don't SWAT me
    if(!get_RC(T))
        return NULL;
    else
        T = get_RC(T);

    //Finding left most child
    while(get_LC(T))
        T = get_LC(T);

    return T;
}

static BST _find_predeccessor(BST T){
    //Entering right child, please don't SWAT me
    if(!get_LC(T))
        return NULL;
    else
        T = get_LC(T);

    //Finding left most child
    while(get_RC(T))
        T = get_RC(T);

    return T;
}

static void _bfs(BST T, int* a, int pos, int max){
    if (T) {
        a[pos] = get_val(T);
    } else {
        a[pos] = X;
    }

    //Making sure the posistion does not get out of bounds, nor misses a node.
    if (pos * 2 + 2 >= max) { return; }
    _bfs(get_LC(T), a, pos * 2 + 1, max);
    _bfs(get_RC(T), a, pos * 2 + 2, max);
}
