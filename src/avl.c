//=============================================================================
// avl.c - AVL-tree based on binary search tree (bst.h/bst.c)
//=============================================================================
#include "../include/avl.h"
#include "../include/global.h"
#define DEBUG 1
//=============================================================================
// local prototypes
//-----------------------------------------------------------------------------
static AVL srr(AVL T);
static AVL slr(AVL T);
static AVL drr(AVL T);
static AVL dlr(AVL T);
static int balance_factor(AVL T);
//=============================================================================
// Public functions, exported via .h-file
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// avl_add: adds the value val to AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_add(AVL T, int val)
{
	if(DEBUG)printf("avl_add (%d)\n",val);
	T = bst_add(T, val);
	return balance(T);
}
//-----------------------------------------------------------------------------
// avl_rem: removes the value val from AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_rem(AVL T, int val)
{
	if(DEBUG)printf("avl_rem (%d)\n",val);
	T = bst_rem(T, val);
	return balance(T);
}
//-----------------------------------------------------------------------------
// balance: balances the AVL tree T if needed
//-----------------------------------------------------------------------------
AVL balance(AVL T)
{
    int balance_factor_root = balance_factor(T);
    if(balance_factor_root >= 2){    //Left is heavier
        if (balance_factor(get_LC(T)) <= -1)
            return drr(T);  //Inner heavy
        else
            return srr(T);  //Outer heavy
    }else if(balance_factor_root <= -2){     //Right is heavier
        if (balance_factor(get_RC(T)) >= 1)
            return dlr(T);  //Inner heavy
        else
            return slr(T);  //Outer heavy
    }
    return T;
}
//=============================================================================
// Private functions, for local use only
//-----------------------------------------------------------------------------
//Function that calculate the balance factor of a node.
//Negative return means right subtree is heavier, otherwise left. Zero is perfectly balanced
static int balance_factor(AVL T){
    return height(get_LC(T)) - height(get_RC(T));
}
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
    AVL temp = T;
    T = get_RC(T);
    AVL temp_2 = get_LC(T);
    set_RC(temp, temp_2);
    set_LC(T, temp);
	return T;
}

//Left-right rotation
static AVL drr(AVL T)
{
	if(DEBUG)printf("drr\n");
	T = slr(get_LC(T));
	return srr(T);
}

//Right-left rotation
static AVL dlr(AVL T)
{
	if(DEBUG)printf("drr\n");
	T = srr(T);
	return slr(T);
}
