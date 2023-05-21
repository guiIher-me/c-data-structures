//@AUTHOR : Guilherme Cardoso Oliveira <guilherme.cardoso-oliveira@unesp.br>
//@lICENSE: MIT
//@DATE   : 2021-04-29

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DATA_STRUCT_NAME "Queue"

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
//QUEUE
typedef struct queue {
	Node head;
	Node tail;
} * Queue;


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
//QUEUE METHODS

// Checks if queue is initialized
bool isInit(Queue queue) {
	return queue != NULL;
}

// Checks if queue is empty
bool isEmpty(Queue queue) {
	return queue->head == NULL;
}

// Ensures that the queue is initialized or generates an error otherwise
void assertInit(Queue queue) {
	if(!isInit(queue)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" isn't initialized!");
		exit(EXIT_FAILURE);
	}
}

// Ensures that the queue isn't empty or generates an error otherwise
void assertNotEmpty(Queue queue) {
	assertInit(queue);
	
	if(isEmpty(queue)) {
		printf("[ERR] ");
		printf(DATA_STRUCT_NAME);
		printf(" is empty!");
		exit(EXIT_FAILURE);
	}
}

// Creates a new Queue
Queue new_queue() {
	Queue queue = (Queue) malloc(sizeof(Queue));

	if(!isInit(queue)) {
		printf("[ERR] Not enough memory");
		exit(EXIT_FAILURE);
	}
	
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

// Adds a new node to last position in the queue
void add(Queue queue, Data data) {
	assertInit(queue);
	Node node = node_new(data);
	
    if(isEmpty(queue))
        queue->head = node;
    else
        queue->tail->next = node;
	
	queue->tail = node;
}

// Returns data from the first node in the queue 
Data peek(Queue queue) {
	assertNotEmpty(queue);
	return queue->head->data;
}

// Returns the number of nodes in the queue
int size(Queue queue) {
	assertInit(queue);
	return node_count(queue->head);
}

// Check if there is a specific data in the queue
bool contains(Queue queue, Data data) {
	assertInit(queue);
	return node_contains(queue->head, data);
}

// Prints all data from nodes in the queue
void print(Queue queue) {
	assertInit(queue);
	node_print(queue->head);
}

// Removes all nodes in the queue
void clear(Queue queue) {
	node_removeAll(queue->head);
	queue->head = NULL;
	queue->tail = NULL;
}

// Removes the first node in the queue
Data pop(Queue queue) {
	Data data  = peek(queue);
	Node head  = queue->head;
    queue->head = head->next;
    free(head);

    if(isEmpty(queue))
        queue->tail = NULL;
     
    return data;
}

//-----------------------------------------------------------
//MAIN

int main() {
	//Example:
	Queue queue = new_queue();
	
	add(queue, 10);
	add(queue, 20);
	add(queue, 30);
	
	print(queue);
	printf("Head: %d\n", peek(queue));
	printf("size: %d\n", size(queue));
	printf("Has 30? %d\n", contains(queue, 30));
	printf("Has 60? %d\n", contains(queue, 60));
	
	pop(queue);
	print(queue);
	
	clear(queue);
	return 0;
}
