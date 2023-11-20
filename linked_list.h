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
void show(LinkedList);
void append(LinkedList *, char *);
int isEmpty(LinkedList);
char *pop(LinkedList *, char *);
char *get(LinkedList *, int);
void appendAll(DoublyLinkedList *, int , ...);