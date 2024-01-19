#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

Stack *createStack();
int isEmptyStack(Node *);
void pushStack(Node **, char *);
char *popStack(Node **);
void showStack(Node *);
void clearStack(Node *);
char *peekStack(Node *);