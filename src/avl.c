//=============================================================================
// avl.c - AVL-tree based on binary search tree (bst.h/bst.c)
//=============================================================================
#include "../include/avl.h"
#define DEBUG 0
//=============================================================================
// local prototypes
//-----------------------------------------------------------------------------
static AVL srr(AVL T);
static AVL slr(AVL T);
static AVL drr(AVL T);
static AVL dlr(AVL T);
//=============================================================================
// Public functions, exported via .h-file
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// avl_add: adds the value val to AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_add(AVL T, int val)
{
	if(DEBUG)printf("avl_add (%d)\n",val);
	// TODO
	return T;
}
//-----------------------------------------------------------------------------
// avl_rem: removes the value val from AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_rem(AVL T, int val)
{
	if(DEBUG)printf("avl_rem (%d)\n",val);
	// TODO
	return T;
}
//-----------------------------------------------------------------------------
// balance: balances the AVL tree T if needed
//-----------------------------------------------------------------------------
AVL balance(AVL T)
{
	// TODO
	return srr(slr(drr(dlr(T))));
}
//=============================================================================
// Private functions, for local use only
//-----------------------------------------------------------------------------
//Right Rotate, return the root of the rotated tree
static AVL srr(AVL T)
{
	if(DEBUG)printf("srr\n");
	AVL new_root = get_LC(T);  //Left child becomes new root
	set_LC(T, get_RC(new_root));   //Preparing the old root with a new left child
	set_RC(new_root, T);   //Old root becomes right child
	return new_root;          //Return the new root
}
static AVL slr(AVL T)
{
   	if(DEBUG)printf("slr\n");
    AVL old_root = T;
    AVL new_root = get_RC(T);
    set_RC(old_root, get_LC(new_root));
    set_LC(new_root, old_root);
	return new_root;
}

//Left-right rotation
static AVL drr(AVL T)
{
	if(DEBUG)printf("drr\n");
	T = slr(T);
	T = srr(T);
	return T;
}

//Right-left rotation
static AVL dlr(AVL T)
{
	if(DEBUG)printf("drr\n");
	T = srr(T);
	T = slr(T);
	return T;
}
