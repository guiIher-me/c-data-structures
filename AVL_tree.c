//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2021-06-29

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DATA_STRUCT_NAME "AVL Tree"
#define ERR_NO_MEMORY "Not enough memory"

//-----------------------------------------------------------
//DATA

typedef int Data;
#define DATA_FORMAT "%d"

//-----------------------------------------------------------
//NODE

typedef struct node {
	Data data;
	int height;
	struct node *left;
	struct node *right;
} * Node;


//-----------------------------------------------------------
//Binary Tree
typedef struct tree {
	Node root;
} * Tree;


//-----------------------------------------------------------
//UTILITY METHODS

void error(char *msg) { 
	printf("\n[ERR] %s", msg);
	exit(1);
}

int max(int a, int b) {
    return (a > b)? a : b;
}

//-----------------------------------------------------------
//NODE METHODS

bool empty(Node node) {
	return node == NULL;
}

Node new_node(Data data) {
	Node node = (Node) malloc(sizeof(Node));
	
	if(empty(node))
		error(ERR_NO_MEMORY);
	
	node->data   = data;
	node->height = 0; //leaf
	node->left   = NULL;
	node->right  = NULL;
	
	return node;
}

int height(Node node) {
    return (empty(node))? -1 : node->height;
}

void updateHeight(Node node) {
	node->height = max(height(node->left), height(node->right))+1;
}

int balance(Node node) {
    return (empty(node))? 0 : height(node->right) - height(node->left);
}

// node = 3
Node rotateToLeft(Node node) {
	//printf("ROTACAO PRA ESQUERDA\n");
	Node right  = node->right; //4
	node->right = right->left; //x
	right->left = node; //3
	
	updateHeight(node );
	updateHeight(right);
		
	return right;
}

//node = 5
Node rotateToRight(Node node) {
	//printf("ROTACAO PRA DIREITA\n");
	Node left   = node->left; //left = 4
	node->left  = left->right; //x
	left->right = node; // 5
	
	updateHeight(node );
	updateHeight(left);
	
	return left;
}

Node rotateToLeftAndRight(Node node) {
	//printf("ROTACAO PRA ESQUERDA/DIREITA\n");
	node->left = rotateToLeft(node->left);
	return rotateToRight(node);
}

Node rotateToRightAndLeft(Node node) {
	//printf("ROTACAO PRA DIREITA/ESQUERDA\n");
	node->right = rotateToRight(node->right);
	return rotateToLeft(node);
}

Node applyRotationTable(Node node, Data data) {
	//printf("Olhando data: %d | B:%d\n", node->data, balance(node));
	int balance_factor = balance(node);
	
	// left left Case
	if (balance_factor < -1 && data < node->left->data)
        return rotateToRight(node);
 
    // Right Right Case
    if (balance_factor > 1 && data > node->right->data)
        return rotateToLeft(node);
	
    // Left Right Case
    if (balance_factor < -1 && data > node->left->data)
		return rotateToLeftAndRight(node);
	 
    // Right Left Case
    if (balance_factor > 1 && data < node->right->data)
		return rotateToRightAndLeft(node);
		
	return node;
}

Node insert_node(Node current, Data data) {
	if(empty(current))
		return new_node(data);
	
	if(data < current->data)
		current->left  = insert_node(current->left , data);
	else
		current->right = insert_node(current->right, data);

	//update height (recursively)
	current->height = 1 + max(height(current->left), height(current->right));
	
	//apply rotation(s)
	return applyRotationTable(current, data);
}

void print_node(Node current) {
	if(empty(current)) return;

	printf(DATA_FORMAT, current->data);
	printf("(");
	print_node(current->left);
	print_node(current->right);
	printf(") ");
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
	//printf("---\n");
}

void print(Tree tree) {
	printf("\n");
	print_node(tree->root);
}

//-----------------------------------------------------------
//MAIN

int main() {
	Tree tree = new_tree();
	
	insert(tree, 1);
	insert(tree, 3);
	insert(tree, 2);
	print(tree);
	
	return 0;
}
