#include "linked_list.h"

LinkedList *createLinkedList()
{
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->head = NULL;
    linkedList->size = 0;
    return linkedList;
}

int isEmpty(LinkedList list)
{
    return list.head == NULL;
}

void append(LinkedList *list, char *item)
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

void show(LinkedList list)
{
    Node *head = list.head;
    printf("\033[1;0m[");
    while (head)
    {
        if (head->next)
            printf("\033[1;32m%d, ", head->data);
        else
            printf("\033[1;32m%d]\n\033[1;0m", head->data);
        head = head->next;
    }
}

char *pop(LinkedList *list, char *item)
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