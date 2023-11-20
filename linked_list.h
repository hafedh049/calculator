#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>
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
void showAllItems(LinkedList);
void append(LinkedList *, char *);
int isEmpty(LinkedList);
int search(LinkedList, char *);
void appendAll(LinkedList *, int, ...);
int pop(LinkedList *, char *);