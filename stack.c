#include "stack.h"

Node *create()
{
    return NULL;
}

void push(Node **stack, char item)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = item;
    new->next = *stack;
    *stack = new;
}

int empty(Node *stack)
{
    return stack == NULL;
}

char pop(Node **stack)
{
    assert(!empty(*stack));
    Node *head = *stack;
    *stack = (*stack)->next;
    char data = head->data;
    free(head);
    return data;
}

void clear(Node **stack)
{
    Node *head;
    while (*stack)
    {
        head = *stack;
        *stack = (*stack)->next;
        free(head);
    }
}

char peek(Node *stack)
{
    assert(!empty(stack));
    return stack->data;
}