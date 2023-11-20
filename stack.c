#include "stack.h"

Stack* createStack()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

void pushStack(Stack *stack, char *item)
{
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode));
    
    newStackNode->data = item;
    newStackNode->next = stack->head;
    stack->head = newStackNode;
}

int isEmptyStack(Stack stack)
{
    return stack.head == NULL;
}

char *popStack(Stack *stack)
{
    assert(!isEmptyStack(*stack));

    StackNode *headReference = (*stack).head;
    
    (*stack).head = (*stack).head->next;
    
    StackNode *popedStackNode = (StackNode *)malloc(sizeof(StackNode));
    
    popedStackNode->data = headReference->data;
    popedStackNode->next = NULL;
    
    free(headReference);
    
    return popedStackNode->data;
}

void clearStack(Stack *stack)
{
    StackNode *head;
    while (stack->head)
    {
        head = stack->head;
        stack->head = stack->head->next;
        free(head);
    }
}

char *peekStack(Stack stack)
{
    assert(!isEmptyStack(stack));
    return stack.head->data;
}