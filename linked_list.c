//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2021-04-27

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DATA_STRUCT_NAME "Linked List"

//-----------------------------------------------------------
//DATA

typedef int Data;
#define DATA_FORMAT "%d"
#define PRINT_SEPARATOR "->"

//-----------------------------------------------------------
//NODE

typedef struct node {
	Data data;
	struct node *next;
} * Node;


//-----------------------------------------------------------
//LINKED LIST
typedef struct linkedlist {
	Node head;
	Node tail;
} * LinkedList;


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

// Checks if list is initialized
bool isInit(LinkedList list) {
	return list != NULL;
}

// Checks if list is empty
bool isEmpty(LinkedList list) {
	return list->head == NULL;
}

// Ensures that the list is initialized or generates an error otherwise
void assertInit(LinkedList list) {
	if(!isInit(list)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" isn't initialized!");
		exit(EXIT_FAILURE);
	}
}

// Ensures that the list isn't empty or generates an error otherwise
void assertNotEmpty(LinkedList list) {
	assertInit(list);
	
	if(isEmpty(list)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" is empty!");
		exit(EXIT_FAILURE);
	}
}

// Creates a new linkedList
LinkedList new_list() {
	LinkedList list = (LinkedList) malloc(sizeof(LinkedList));

	if(!isInit(list)) {
		printf("[ERR] Not enough memory");
		exit(EXIT_FAILURE);
	}
	
	list->head = NULL;
	list->tail = NULL;
	return list;
}

// Adds a new node to first position in the list
void addFirst(LinkedList list, Data data) {
	assertInit(list);
	Node node = node_new(data);
	
	if(isEmpty(list))
        list->tail = node;
	
    node->next = list->head;
    list->head = node;
}

// Adds a new node to last position in the list
void addLast(LinkedList list, Data data) {
	assertInit(list);
	Node node = node_new(data);
	
    if(isEmpty(list))
        list->head = node;
    else
        list->tail->next = node;
	
	list->tail = node;
}

// Returns data from the first node in the list 
Data getFirst(LinkedList list) {
	assertNotEmpty(list);
	return list->head->data;
}

// Returns data from the last node in the list 
Data getLast(LinkedList list) {
	assertNotEmpty(list);
	return list->tail->data;
}

// Returns the number of nodes in the list
int size(LinkedList list) {
	assertInit(list);
	return node_count(list->head);
}

// Check if there is a specific data in the list
bool contains(LinkedList list, Data data) {
	assertInit(list);
	return node_contains(list->head, data);
}

// Prints all data from nodes in the list
void print(LinkedList list) {
	assertInit(list);
	node_print(list->head);
}

// Removes all nodes in the list
void clear(LinkedList list) {
	node_removeAll(list->head);
	list->head = NULL;
	list->tail = NULL;
}

// Removes the first node in the list
Data removeFirst(LinkedList list) {
	Data data  = getFirst(list);
	Node head  = list->head;
    list->head = head->next;
    free(head);

    if(isEmpty(list))
        list->tail = NULL;
     
    return data;
}

// Removes the last node in the list
Data removeLast(LinkedList list) {
	Data data = getLast(list);
    if(empty(list->head->next)) { //if has only one element
        clear(list);
        return data;
    }

    Node penult = node_getpenult(list->head);
    penult->next = NULL;
    free(list->tail);
    list->tail = penult;

    return data;
}


//-----------------------------------------------------------
//MAIN

int main() {
	//Example:
	LinkedList list = new_list();
	
	addFirst(list, 30);
	addLast(list , 40);
	addFirst(list, 20);
	addFirst(list, 10);
	addLast(list , 50);
	
	print(list);
	printf("First: %d\n", getFirst(list));
	printf("Last: %d\n", getLast(list));
	printf("size: %d\n", size(list));
	printf("Has 30? %d\n", contains(list, 30));
	printf("Has 60? %d\n", contains(list, 60));
	
	removeFirst(list);
	removeLast(list);
	
	addFirst(list, 11);
	addLast(list, 51);
	print(list);
	
	clear(list);
	return 0;
}
