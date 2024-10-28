#include "linkedlist.h"

LinkedList* createLinkedList(void)
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void insertStart(LinkedList* list, void* entry)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = list->head;
    
    list->head = newNode;
}

void* removeStart(LinkedList* list)
{
    LinkedListNode* node = list->head;
    void* data;
    if (node != NULL) { /* If the node is not the last one, make the head be the next node */
        list->head = node->next;
    }
    node->next = NULL;

    data = node->data;
    free(node);
    return data; /* Return the data of the node, so the programmer can free it appropriately */
}

void freeLinkedList(LinkedList* list, freeNode funcPtr)
{
    LinkedListNode *node, *nextNode;
    node = list->head;
    while (node != NULL) { /* If the node exists */
        nextNode = node->next; /* Get the next node */
        funcPtr(node->data); /* Free the data in the node */
        free(node); /* Free the node */
        node = nextNode; /* Set the current node as the next one */
    }
    free(list); /* Finally free the linked list */
}