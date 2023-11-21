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
void showLinkedist(LinkedList);
void appendLinkedist(LinkedList *, char *);
int isEmptyLinkedist(LinkedList);
char *popLinkedist(LinkedList *, char *);
char *getLinkedist(LinkedList *, int);
void appendAllLinkedist(LinkedList *, int , ...);