//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2021-06-01

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DATA_STRUCT_NAME "Binary Tree"
#define ERR_NO_MEMORY "Not enough memory"

//-----------------------------------------------------------
//DATA

typedef int Data;
#define DATA_FORMAT "%d"

//-----------------------------------------------------------
//NODE

typedef struct node {
	Data data;
	struct node *left; //child
	struct node *right; //child
} * Node;


//-----------------------------------------------------------
//Binary Tree
typedef struct tree {
	Node root;
} * Tree;


//-----------------------------------------------------------
//NODE METHODS

void error(char *msg) {
	printf("\n[ERR] %s", msg);
	exit(1);
}

bool empty(Node node) {
	return node == NULL;
}

Node new_node(Data data) {
	Node node = (Node) malloc(sizeof(Node));
	
	if(empty(node))
		error(ERR_NO_MEMORY);
	
	node->data  = data;
	node->left  = NULL;
	node->right = NULL;
	
	return node; 
}

bool hasLeft(Node node) {
	return !empty(node) && !empty(node->left);
}

bool hasRight(Node node) {
	return !empty(node) && !empty(node->right);
}

bool hasOnlyLeft(Node node) {
	return hasLeft(node) && !hasRight(node);
}

bool hasOnlyRight(Node node) {
	return !hasLeft(node) && hasRight(node);
}

bool isLeaf(Node node) {
	return !hasLeft(node) && !hasRight(node);
}

Node insert_node(Node current, Data data) {
	if(empty(current))
		return new_node(data);

	if(data < current->data)
		current->left  = insert_node(current->left , data);
	else
		current->right = insert_node(current->right, data);
		
	return current;
}

int count_node(Node current) {
	if(empty(current)) return 0;
	return 1 + count_node(current->left) + count_node(current->right);
}

int count_childrens(Node node) {
	return hasLeft(node) + hasRight(node);
}

void print_node(Node current) {
	if(empty(current)) return;

	printf(DATA_FORMAT, current->data);
	printf("(");
	print_node(current->left);
	print_node(current->right);
	printf(") ");
}

bool exists_node(Node current, Data data) {
	if(empty(current)) return false;
	
	if(data < current->data)
		return exists_node(current->left, data);
	
	if(data > current->data)
		return exists_node(current->right, data);
	
	return true;
}

Node search_node(Node current, Data data, Node *parent) {
	if(empty(current) || data == current->data)
		return current;
	
	*parent = current;
	
	if(data < current->data)
		return search_node(current->left , data, parent);
	
	if(data > current->data)
		return search_node(current->right, data, parent);
	
	return NULL; //dead code
}

		
Node kill_node(Node root, Node node, Node *children, Node new_children) {
	free(node);
	
	if(empty(root))
		return new_children;
	
	*children = new_children;
	return root;
}

Node killNodeWithTwoChildrens(Node root, Node node, Node *children) {
	Node ancestral    = node;
	Node new_children = ancestral->left;
	while(!empty(new_children->right)) {
		ancestral    = new_children;
		new_children = new_children->right;	
	}
	
	if(ancestral != node) {
		new_children->left = node->left;
		ancestral->right = NULL;
	}
	
	new_children->right = node->right;
	return kill_node(root, node, children, new_children);
}

Node remove_node(Node root, Data data) {
	Node parent = NULL;
	Node node   = search_node(root, data, &parent);
	
	Node *children;
	if(node == root)
		root = NULL; //flag
	else if(node == parent->left)
		children = &(parent->left);
	else
		children = &(parent->right);
	
	
	if(empty(node))
		return root;
	
	if(isLeaf(node))
		return kill_node(root, node, children, NULL);
	
	if(hasOnlyLeft(node))
		return kill_node(root, node, children, node->left);
		
	if(hasOnlyRight(node))
		return kill_node(root, node, children, node->right);
		
	return killNodeWithTwoChildrens(root, node, children);
}

//-----------------------------------------------------------
//TREE METHODS

bool isEmpty(Tree tree) {
	return tree == NULL;
}

Tree new_tree() {
	Tree tree = (Tree) malloc(sizeof(Tree));
	
	if(isEmpty(tree))
		error(ERR_NO_MEMORY);
		
	tree->root = NULL;
	
	return tree;
}

void insert(Tree tree, Data data) {
	tree->root = insert_node(tree->root, data);
}

bool exists(Tree tree, Data data) {
	return exists_node(tree->root, data);
}

int count(Tree tree) {
	return count_node(tree->root);
}

void print(Tree tree) {
	printf("\n");
	print_node(tree->root);
}

void drop(Tree tree, Data data) {
	tree->root = remove_node(tree->root, data);
}

//-----------------------------------------------------------
//MAIN

int main() {
	Tree tree = new_tree();
	
	insert(tree, 10);
	insert(tree,  8);
	insert(tree,  6);
	insert(tree, 14);
	insert(tree, 16);
	insert(tree, 12);
	insert(tree, 11);
	insert(tree,  9);
	
	print(tree);
	
	drop(tree, 8);
	
	print(tree);
		
	return 0;
}
