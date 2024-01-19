#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *head;
    Node *tail;
} Queue;

Queue create();
int empty(Queue);
void push(Queue *, char);
char pop(Queue *);
void show(Queue);
void clear(Queue *);
void pushMany(Queue *, int, ...);