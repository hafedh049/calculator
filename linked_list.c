#include "linked_list.h"

LinkedList *createLinkedList()
{
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->head = NULL;
    return linkedList;
}

int isEmpty(LinkedList list)
{
    return list.head == NULL;
}

void append(LinkedList *list, int item)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = item;
    node->next = NULL;
    if (isEmpty(*list))
    {
        node->previous = NULL;
        list->head = node;
    }
    else
    {
        Node *last = list->head;
        while (last->next)
            last = last->next;
        node->previous = last;
        last->next = node;
    }
}

void appendAll(LinkedList *list, int itemCount, ...)
{
    va_list args;
    va_start(args, itemCount);
    for (int index = 0; index < itemCount; index++)
        append(list, va_arg(args, int));
}

void showAllItems(LinkedList list)
{
    Node *head = list.head;
    printf("\033[1;0m[");
    while (head)
    {
        if (head->next)
            printf("\033[1;32m%d, ", head->data);
        else
            printf("\033[1;32m%d]", head->data);
        head = head->next;
    }
    printf("\033[1;0m");
}

int search(LinkedList l, int item)
{
    assert(!isEmpty(l));
    Node *head = l.head;
    while (head)
    {
        if (head->data == item)
            return 1;
        head = head->next;
    }
    return 0;
}

int pop(LinkedList *list, int item)
{
    assert(!isEmpty(*list));
    if (list->head->data == item)
        return popFirst(list);
    Node *head = list->head;
    while (head->next && head->next->data != item)
        head = head->next;
    if (head->next)
    {
        Node *aux = head->next;
        int value = aux->data;
        head->next = aux->next;
        free(aux);
        return value;
    }
    else
        return -1;
}

int getSize(LinkedList list, Node *head)
{
    if (isEmpty(list))
        return 0;
    if (head)
        return 1 + getSize(list, head->next);
}