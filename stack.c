//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2021-04-28

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DATA_STRUCT_NAME "Stack"

//-----------------------------------------------------------
//DATA

typedef int Data;
#define DATA_FORMAT "%d"
#define PRINT_SEPARATOR "<-"

//-----------------------------------------------------------
//NODE

typedef struct node {
	Data data;
	struct node *next;
} * Node;


//-----------------------------------------------------------
//STACK
typedef struct stack {
	Node top;
} * Stack;


//-----------------------------------------------------------
//NODE METHODS

// Checks if a node is empty
bool empty(Node node) {
	return node == NULL;
}

// Allocate a new node 
Node node_alloc() {
	Node node = (Node) malloc(sizeof(Node));
	
	if(empty(node)) {
		printf("[ERR] Not enough memory");
		exit(EXIT_FAILURE);
	}
	
	return node;
}

// Creates a new node and fill it with data
Node node_new(Data data) {
	Node node  = node_alloc();
	node->data = data;
	node->next = NULL;
	
	return node;
}

// Get a node from a specified position
Node node_getpos(Node node, int position) {
	if(position <= 0 || empty(node)) {
		printf("[ERR] Invalid parameter position");
		exit(EXIT_FAILURE);
	}
    
    if(position == 1)
        return node;

    return node_getpos(node->next, position-1);
}

// Get penult node or exit with error otherwise
Node node_getpenult(Node node) {
	if(empty(node) || empty(node->next)) {
		printf("[ERR] Hasn't penult node!");
		exit(EXIT_FAILURE);
	}
	
	if(empty(node->next->next))
		return node;
	
	return node_getpenult(node->next);	
}

// prints all linked nodes
void node_print(Node node) {
	if(empty(node)) {
		printf("[NULL]\n");
		return;	
	}
	
	printf("[");
	printf(DATA_FORMAT, node->data);
	printf("]");
	printf(PRINT_SEPARATOR);
	
	return node_print(node->next);
}

// Checks if a specified data exists in a group of linked nodes
bool node_contains(Node node, Data data) {
	if(empty(node))
		return false;
	
	if(node->data == data)
		return true;
	
	return node_contains(node->next, data);
}

// Returns the number of nodes in a group of linked nodes
int node_count(Node node) {
	if(empty(node)) return 0;
	return 1 + node_count(node->next);
}

// Remove all nodes from a group of linked nodes
void node_removeAll(Node node) {
	if(empty(node)) return;
	Node next = node->next;
	free(node);
	return node_removeAll(next);
}


//-----------------------------------------------------------
//LINKEDLIST METHODS

// Checks if stack is initialized
bool isInit(Stack stack) {
	return stack != NULL;
}

// Checks if stack is empty
bool isEmpty(Stack stack) {
	return stack->top == NULL;
}

// Ensures that the stack is initialized or generates an error otherwise
void assertInit(Stack stack) {
	if(!isInit(stack)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" isn't initialized!");
		exit(EXIT_FAILURE);
	}
}

// Ensures that the stack isn't empty or generates an error otherwise
void assertNotEmpty(Stack stack) {
	assertInit(stack);
	
	if(isEmpty(stack)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" is empty!");
		exit(EXIT_FAILURE);
	}
}

// Creates a new stack
Stack new_stack() {
	Stack stack = (Stack) malloc(sizeof(Stack));

	if(!isInit(stack)) {
		printf("[ERR] Not enough memory");
		exit(EXIT_FAILURE);
	}
	
	stack->top = NULL;
	return stack;
}

// Adds a new node to first position in the list
void push(Stack stack, Data data) {
	assertInit(stack);
	Node node = node_new(data);

    node->next = stack->top;
    stack->top = node;
}


// Returns data from the first node in the list 
Data peek(Stack stack) {
	assertNotEmpty(stack);
	return stack->top->data;
}


// Returns the number of nodes in the stack
int size(Stack stack) {
	assertInit(stack);
	return node_count(stack->top);
}

// Check if there is a specific data in the stack
bool contains(Stack stack, Data data) {
	assertInit(stack);
	return node_contains(stack->top, data);
}

// Prints all data from nodes in the stack
void print(Stack stack) {
	assertInit(stack);
	node_print(stack->top);
}

// Removes all nodes in the stack
void clear(Stack stack) {
	node_removeAll(stack->top);
	stack->top = NULL;
}

// Removes the first node in the list
Data pop(Stack stack) {
	Data data = peek(stack);
	Node top  = stack->top;
    stack->top = top->next;
    free(top);

    if(isEmpty(stack))
        stack->top = NULL;
     
    return data;
}


//-----------------------------------------------------------
//MAIN

int main() {
	//Example:
	Stack stack = new_stack();
	
	push(stack, 30);
	push(stack, 20);
	push(stack, 10);
	
	print(stack);
	printf("Top: %d\n", peek(stack));
	printf("size: %d\n", size(stack));
	printf("Has 30? %d\n", contains(stack, 30));
	printf("Has 60? %d\n", contains(stack, 60));
	
	pop(stack);
	pop(stack);
	print(stack);
	
	clear(stack);
	return 0;
}
