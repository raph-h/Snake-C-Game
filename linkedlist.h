#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A node for the linked list */
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

/* The struct containing linked list nodes */
typedef struct LinkedList {
    LinkedListNode* head;
} LinkedList;

/* Function which will create a linked list */
LinkedList* createLinkedList(void);
/* Add an entry to the linked list */
void insertStart(LinkedList* list, void* entry);
/* Remove an entry at the start of the linked list */
void* removeStart(LinkedList* list);

/* Function to free a node */
typedef void (*freeNode)(void* data);
/* Free the linked list node, requiring a function to free each node */
void freeLinkedList(LinkedList* list, freeNode funcPtr);

#endif