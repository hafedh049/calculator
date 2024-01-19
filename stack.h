#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

Node *create();
int empty(Node *);
void push(Node **, char);
char pop(Node **);
void show(Node *);
void clear(Node **);
char peek(Node *);