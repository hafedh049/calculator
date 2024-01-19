#include "queue.h"

Queue create()
{
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

void push(Queue *queue, int item)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = item;
    new->next = NULL;
    if (empty(*queue))
        queue->head = new;
    else
        queue->tail->next = new;
    queue->tail = new;
}

int empty(Queue queue)
{
    return queue.head == NULL && queue.tail == NULL;
}

char pop(Queue *queue)
{
    assert(!isEmpty(*queue));

    if (queue->head == queue->tail)
    {
        char data = queue->head->data;
        free(queue->head);
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
    {
        char data = queue->head->data;
        Node *headReference = queue->head;
        queue->head = queue->head->next;
        free(headReference);
    }
    return data;
}

void show(Queue queue)
{
    /*
        Black: 30
        Red: 31
        Green: 32
        Yellow: 33
        Blue: 34
        Magenta: 35
        Cyan: 36
        White: 37
        Reset: 0
        \033[1;<color code>m
    */
    printf("\033[1;33m\n\n---------------------------\n\n");

    if (empty(queue))
    {
        printf("This queue is empty x(");
        printf("\033[1;33m\n\n---------------------------\n\n");
        printf("\033[1;0m");
        return;
    }
    const Node *head = queue.head;
    while (head)
    {
        if (head->next)
            printf("\033[1;32m| %d | -> ", head->data);
        else
            printf("\033[1;32m| %d |", head->data);
        head = head->next;
    }
    printf("\033[1;33m\n\n---------------------------\n\n");
    printf("\033[1;0m");
}

void clear(Queue *queue)
{
    while (!empty(*queue))
        pop(queue);
}

// variadics macro
void pushMany(Queue *queue, int itemsCount, ...)
{
    va_list args;
    va_start(args, itemsCount);
    for (int index = 0; index < itemsCount; index++)
        push(queue, va_arg(args, int));
}