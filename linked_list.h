#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
int search(LinkedList, char *);
int pop(LinkedList *, char *);