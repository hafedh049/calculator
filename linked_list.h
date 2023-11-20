#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

typedef struct Node
{
    char *data;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct LinkedList
{
    Node *head;
    int size;
} LinkedList;

LinkedList *createLinkedList();
void showLinkedist(LinkedList);
void appendLinkedist(LinkedList *, char *);
int isEmptyLinkedist(LinkedList);
char *popLinkedist(LinkedList *, char *);
char *getLinkedist(LinkedList *, int);
void appendAllLinkedist(LinkedList *, int , ...);