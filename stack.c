#include "stack.h"

Stack* createStack()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

void pushStack(Stack *stack, char *item)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    newNode->data = item;
    newNode->next = stack->head;
    stack->head = newNode;
}

int isEmptyStack(Stack stack)
{
    return stack.head == NULL;
}

char *popStack(Stack *stack)
{
    assert(!isEmpty(*stack));

    Node *headReference = (*stack).head;
    
    (*stack).head = (*stack).head->next;
    
    Node *popedNode = (Node *)malloc(sizeof(Node));
    
    popedNode->data = headReference->data;
    popedNode->next = NULL;
    
    free(headReference);
    
    return popedNode->data;
}

void clearStack(Stack *stack)
{
    Node *head;
    while ((*stack).head)
    {
        head = (*stack).head;
        (*stack).head = (*stack).head->next;
        free(head);
    }
}

int peekStack(Stack stack)
{
    assert(!isEmpty(stack));
    return stack.head->data;
}