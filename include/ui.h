// ui.h
#include <stdio.h>
#include <string.h>
#include "bt.h"
#include "bst.h"
#include "avl.h"
#ifndef UI_H
#define UI_H
#define BUFSIZE 100
#define TREE_WIDTH 80
void print_tree(BST T);
void print_array(int* a, int size);
void print_2d(int* a, int maxnodes);
void run(char mode, bool echo);
#endif
