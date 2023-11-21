#include "linked_list.h"
#include "ctype.h"

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
    LinkedListNode *linkedListNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    linkedListNode->data = item;
    linkedListNode->next = NULL;
    if (isEmptyLinkedist(*list))
    {
        linkedListNode->previous = NULL;
        list->head = linkedListNode;
    }
    else
    {
        LinkedListNode *last = list->head;
        while (last->next)
            last = last->next;
        linkedListNode->previous = last;
        last->next = linkedListNode;
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
    LinkedListNode *head = list.head;
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

    LinkedListNode *prev = NULL;
    LinkedListNode *current = list->head;

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
    LinkedListNode *head = list->head;
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

int isNumber(char *num)
{
    int i = 0;
    while (num[i])
    {
        if ((*(num + i) == '-' || *(num + i) == '+') && (*(num + i + 1)))
        {
            i += 1;
            continue;
        }
        else if (!isdigit(*(num + i)))
            return 0;

        i += 1;
    }
    return 1;
}

int isValidInfixExpression(LinkedList *expression)
{

    LinkedListNode *prev = NULL, *current = expression->head;

    while (current)
    {
        prev = current;
        current = current->next;
        if (isNumber(prev->data) && current == NULL)
            return 1; 
        else if((!isNumber(prev->data) && current == NULL) || (isNumber(prev->data) && isNumber(current->data)) || ((!isNumber(prev->data) && !isNumber(current->data))))
            return 0;
    }
    
    return 1;
}

int *getMaxWeight(LinkedList *expression){
    
    int indx = 0,max = 0;
    LinkedListNode *head = expression->head;

    int *aux = (int *)malloc(2 * sizeof(int));

    while (head)
    {
        if(head->weight == 2)
        {
            aux[0] = indx;
            aux[1] = 2;
            return aux;
        }
            
        else if(head->weight > max)
            max = head->weight;
        head = head->next;    
    }

    aux[0] = indx;
    aux[1] = max;        

    return aux;
}

char *calculateResult(LinkedList *expression){
    if(isValidInfixExpression(expression)){

        double result = 0;

        int *aux = getMaxWeight(expression);

        while(*(aux + 1) > 1){
            
        }

        return ;
    }
    else
        return "INVALID OPERATION";
}