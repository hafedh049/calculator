#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode
{
    char *data;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *head;
} Stack;

Stack *createStack();
int isEmptyStack(Stack);
void pushStack(Stack *, char *);
char *popStack(Stack *);
void showStack(Stack);
void clearStack(Stack *);
int peekStack(Stack);