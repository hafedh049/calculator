#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *head;
} Stack;

Stack *createStack();
int isEmptyStack(Stack);
void pushStack(Stack *, char *);
char *popStack(Stack *);
void showStack(Stack);
void clearStack(Stack *);
int peekStack(Stack);