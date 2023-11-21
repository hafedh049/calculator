#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

typedef struct LinkedListNode
{
    char *data;
    int weight;
    struct LinkedListNode *next;
    struct LinkedListNode *previous;
} LinkedListNode;

typedef struct LinkedList
{
    LinkedListNode *head;
    int size;
} LinkedList;

LinkedList *createLinkedList();
void showLinkedList(LinkedList);
void appendLinkedList(LinkedList *, char *);
int isEmptyLinkedList(LinkedList);
char *popLinkedList(LinkedList *, char *);
char *getLinkedList(LinkedList *, int);
void appendAllLinkedList(LinkedList *, int, ...);