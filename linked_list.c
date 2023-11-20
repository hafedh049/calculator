#include "linked_list.h"

LinkedList *createLinkedList()
{
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->head = NULL;
    linkedList->size = 0;
    return linkedList;
}

int isEmptyLinkedist(LinkedList list)
{
    return list.head == NULL;
}

void appendLinkedist(LinkedList *list, char *item)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = item;
    node->next = NULL;
    if (isEmptyLinkedist(*list))
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

void appendAllLinkedist(LinkedList *list, int itemCount, ...)
{
    va_list args;
    va_start(args, itemCount);
    for (int index = 0; index < itemCount; index++)
        appendLinkedist(list, va_arg(args, char *));
}

void showLinkedist(LinkedList list)
{
    Node *head = list.head;
    printf("\033[1;0m[");
    while (head)
    {
        if (head->next)
            printf("\033[1;32m%s, ", head->data);
        else
            printf("\033[1;32m%s\033[1;0m]\n", head->data);
        head = head->next;
    }
}

char *popLinkedist(LinkedList *list, char *item)
{
    assert(!isEmptyLinkedist(*list));

    Node *prev = NULL;
    Node *current = list->head;

    while (current != NULL && strcmp(current->data, item) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL)
    {
        char *value = current->data;

        if (prev != NULL)
            prev->next = current->next;
        else
            list->head = current->next;

        free(current);
        return value;
    }
    else
        return NULL;
}

char *getLinkedist(LinkedList *list, int index)
{
    assert(!isEmptyLinkedist(*list));
    int counter = -1;
    Node *head = list->head;
    while (head)
    {
        counter++;
        if (counter == index)
            break;
        head = head->next;
    }
    assert(counter == index);
    return head->data;
}