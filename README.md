# Lab: tree-based data structures
This document provides a cheat-sheet on how to work with the provided
start-code.

## Use available options
```
$ ./build/tree -h
USAGE: tree [flags]
	-h	-- help
	-m avl	-- AVL mode
	-e	-- echo input
```

As shown above, you can specify if the program should use a BST or an AVL tree.
The default is BST, and you can change it by setting the AVL mode:
- Run in BST mode: `./build/tree`
- Run in AVL mode: `./build/tree -m avl`

The echo option is useful if you want to redirect input from a file. It will
cause each input to be printed to stdout.
- Run normally: `./build/tree`
- Run with input from file: `./build/tree -e < some_input.txt`
- Run with input from file and output to another file:
	`./build/tree -e < some_input.txt > output.txt` 
