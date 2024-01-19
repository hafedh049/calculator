#include "stack.h"

Node *create()
{
    return NULL;
}

void push(Node **stack, char *item)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = item;
    new->next = *stack;
    *stack = new;
}

int isEmpty(Node *stack)
{
    return stack == NULL;
}

char *pop(Stack *stack)
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