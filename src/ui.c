//ui.c
#include "../include/ui.h"
#include "../include/global.h"
#include <math.h>
#include <stdio.h>
static bool echo = false;

static void ui_line(char * string, char c, int n);
//-----------------------------------------------------------------------------
// prints the BST T
//-----------------------------------------------------------------------------
void print_tree(BST T)
{
	int max_n = pow(2,height(T));
	int* arr = (int*)calloc(max_n,sizeof(int));
	bfs(T, arr, max_n);
	if(!T)
		printf("\nTree is empty\n\n\n");
	else
		print_2d(arr, max_n-1);
	printf("Size:\t\t%d\n", size(T));
	printf("Height:\t\t%d\n", height(T));
	printf("Preorder:\t");	preorder(T,arr);		print_array(arr,size(T));
	printf("Inorder:\t");	inorder(T,arr);			print_array(arr,size(T));
	printf("Postorder:\t");	postorder(T,arr);		print_array(arr,size(T));
	printf("BFS star:\t");bfs(T,arr,max_n);			print_array(arr,max_n-1);
	free(arr);
}
//-----------------------------------------------------------------------------
// prints the contents of integer array a from 0 up to size
//-----------------------------------------------------------------------------
void print_array(int* a, int size)
{
	printf("[");
	if(size == 0){printf("]\n");return;}
	for(int i = 0 ; i < size ; i++)
		if(a[i] != X)
			printf("%d%s",a[i],i<size-1?", ":"]");
		else
			printf("'*'%s",i<size-1?", ":"]");
	printf("\n");
}
//-----------------------------------------------------------------------------
// prints a tree, represented by the BFS order star array a of size maxnodes
// in a 2-dimensional way
//-----------------------------------------------------------------------------
void print_2d(int* a, int maxnodes) // Works good up to 5 height
{   // 0, 2, 6, 14
    // 1, 3, 7, 15
    printf("\nTree 2d\n");

    // 1, 3, 7, 15
    printf("\nTree 2d\n");

    int tree_width = (maxnodes * 5  +1);
    int new_row = 0;
    int per_row = 1; // How many numbers per row
    for(int i = 0; i < maxnodes; i++) {

        // Prepare output buffer
        char buff[5];
        if (a[i] == X) {
            sprintf(buff, "*");
        } else {
            sprintf(buff, "%d",a[i]);
        }
        // Print out one number
        ui_line(buff, ' ', (tree_width/per_row) + 1);

        // for each new line
        if (i == new_row) {
            per_row *= 2; // Each previous number spits too two more numbers
            new_row = new_row * 2 + 2;
            printf("\n");
        }
    }
    printf("\n");
}
//-----------------------------------------------------------------------------
// prints the menu
//-----------------------------------------------------------------------------
void print_menu()
{
	printf("********************************\n");
	printf("m : menu\n");
	printf("t : display tree\n");
	printf("a : add value\n");
	printf("d : delete value\n");
	printf("f : test membership\n");
	printf("q : quit\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
//-----------------------------------------------------------------------------
// gets an input character
//-----------------------------------------------------------------------------
char get_choice(char* prompt)
{
	printf("%s", prompt);
	char buf[BUFSIZE];
	fgets(buf, BUFSIZE-1, stdin);
	if(echo)printf("%c\n", buf[0]);
	return buf[0];
}
//-----------------------------------------------------------------------------
// gets an input integer
//-----------------------------------------------------------------------------
int get_int(char* prompt)
{
	printf("%s",prompt);
	char buf[BUFSIZE];
	fgets(buf,BUFSIZE-1,stdin);
	if(!isdigit(buf[0]))return X;
	return atoi(buf);
}
//-----------------------------------------------------------------------------
// gets input and adds an element to T
//-----------------------------------------------------------------------------
BST ui_add(BST T)
{
	int val;
	do{
		val = get_int("Enter value to be added> ");
		if(val == X)printf("Error: not allowed in tree\n");
	}while(val == X);
	if(echo)printf("%d\n", val);
	return add(T, val);
}
//-----------------------------------------------------------------------------
// gets input and removes and element from T
//-----------------------------------------------------------------------------
BST ui_rem(BST T)
{
	int val;
	do{
		val = get_int("Enter value to be deleted> ");
		if(val == X)printf("Error: not allowed in tree\n");
	}while(val == X);
	if(echo)printf("%d\n", val);
	return rem(T, val);
}
//-----------------------------------------------------------------------------
// gets input and searches for element in T
//-----------------------------------------------------------------------------
void ui_find(BST T)
{
	int val;
	do{
		val = get_int("Enter value to search for> ");
		if(val == X)printf("Error: not allowed in tree\n");
	}while(val == X);
	if(echo)printf("%d\n", val);
	printf("%d is a%smember\n", val, is_member(T,val)?" ":" non-");
}
//-----------------------------------------------------------------------------
// runs the menu and system
// m=='a' --> AVL mode, m!='a' BST mode
// e==true --> echo input, e==false --> no echo
//-----------------------------------------------------------------------------
void run(char m, bool e)
{
	char val;
	BST T = NULL;
	add = (m=='a')? avl_add: bst_add;	// setting "polymorphic" function for add
	rem = (m=='a')? avl_rem: bst_rem;	// setting "polymorphic" function for rem
	echo = e;
	printf("[INFO] running in %s mode\n",m=='a'?"AVL":"BST");
	print_menu();
	do {
		val = get_choice("menu> ");
		switch(val)
		{
			case 'm': print_menu(); 						break;
			case 't': print_tree(T); 						break;
			case 'a': T = ui_add(T); 						break;
			case 'd': T = ui_rem(T); 						break;
			case 'f': ui_find(T); 							break;
			case 'q': 						 				break;
			default	: printf("Unknown command (%c)\n",val);	break;
		}
	} while(val != 'q');
}


static void ui_line(char * string, char c, int n)
{
    if (strlen(string) > n) { return; }

    double new_width = n - strlen(string);
    double side = round(new_width/2);
    for (int i = 0; i <= n; i++) {
        if (i >= side && i <=side+strlen(string)) {
            printf("%s", string);
            i+=strlen(string);
        } else {
            printf("%c", c);
        }
    }
}
