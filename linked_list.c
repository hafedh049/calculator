#include "linked_list.h"
#include "stack.c"
#include "ctype.h"

LinkedList *createLinkedList()
{
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->head = NULL;
    linkedList->size = 0;
    return linkedList;
}

int isEmptyLinkedList(LinkedList list)
{
    return list.head == NULL;
}

int isNumber(char *num)
{
    char *endPtr;

    strtod(num, &endPtr);

    if (endPtr == num || *endPtr != '\0')
        return 0;

    if (num[0] == '-' && isdigit(num[1]))
        return 1;

    return 1;
}

void appendLinkedList(LinkedList *list, char *item)
{
    LinkedListNode *linkedListNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    linkedListNode->data = item;
    linkedListNode->weight = isNumber(item) ? 0 : !strcmp(item, "+") || !strcmp(item, "-") ? 1 : 2;
    linkedListNode->next = NULL;
    if (isEmptyLinkedList(*list))
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
    list->size += 1;
}

void appendAllLinkedList(LinkedList *list, int itemCount, ...)
{
    va_list args;
    va_start(args, itemCount);
    for (int index = 0; index < itemCount; index++)
        appendLinkedList(list, va_arg(args, char *));
}

void showLinkedList(LinkedList list)
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

void clearLinkedList(LinkedList **list)
{
    LinkedListNode *current = (*list)->head;
    LinkedListNode *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    (*list)->head = NULL;
}

LinkedListNode *getLastLinkedList(LinkedList list)
{
    if(list.head == NULL)
        return NULL;

    LinkedListNode *node = list.head;

    while (node->next)
        node = node->next;

    return node;
}

LinkedListNode *getLinkedListNode(LinkedList *list, int index)
{
    assert(!isEmptyLinkedList(*list));
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
    return head;
}

char *toString(LinkedList *list)
{
    if (list == NULL || list->head == NULL || list->size == 0)
        return "";

    char *result = NULL;
    int resultSize = 0;

    LinkedListNode *current = list->head;

    while (current != NULL)
    {
        int dataSize = strlen(current->data);

        result = (char *)realloc(result, resultSize + dataSize + 1);

        strcpy(result + resultSize, current->data);

        resultSize += dataSize;

        current = current->next;
    }

    return result;
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
        else if ((!isNumber(prev->data) && current == NULL) ||
                 (isNumber(prev->data) && isNumber(current->data)) ||
                 ((!isNumber(prev->data) && !isNumber(current->data))))
            return 0;
    }

    return 1;
}

int *getMaxWeight(LinkedList *expression)
{
    int index = -1, maxWeight = 0;
    int *result = (int *)malloc(2 * sizeof(int));

    LinkedListNode *current = expression->head;
    int currentIndex = 0;

    while (current != NULL) {

        if (current->weight == 2) {
            result[0] = currentIndex;
            result[1] = 2;
            return result;
        } else if (current->weight > maxWeight) {
            maxWeight = current->weight;
            index = currentIndex;
        }

        currentIndex++;
        current = current->next;
    }

    result[0] = index;
    result[1] = maxWeight;

    return result;
}

double convertToDouble(char *str)
{
    char *endPtr;
    int isNegative = 0;

    if (*str == '-')
    {
        isNegative = 1;
        str++;
    }

    double result = strtod(str, &endPtr);

    return isNegative ? -result : result;
}

void updateState(LinkedList **expression, int targetIndx)
{ 
    LinkedListNode *item = getLinkedListNode(*expression, targetIndx);
    double res;

    if (!strcmp(item->data, "*"))
        res = convertToDouble(item->previous->data) * convertToDouble(item->next->data);
    else
        res = convertToDouble(item->previous->data) / convertToDouble(item->next->data);

    LinkedListNode *newItem = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    newItem->data = (char *)malloc(20 * sizeof(char));
    newItem->weight = 0;

    sprintf(newItem->data, "%.1f", res);

    LinkedListNode *op1 = item->previous;
    LinkedListNode *op2 = item->next;

    if (op1->previous == NULL && op2->next == NULL)
    {
        newItem->next = NULL;
        newItem->previous = NULL;
        (*expression)->head = newItem;
    }
    else
    {
       
        if (op1->previous == NULL)
        {
            (*expression)->head = newItem;
            newItem->previous = NULL;
            newItem->next = op2->next;
            op2->next->previous = newItem;
        }
        else if (op2->next == NULL)
        {
            op1->previous->next = newItem;
            newItem->previous = op1->previous;
            newItem->next = NULL;
        }
        else
        {
            newItem->previous = op1->previous;
            op1->previous->next = newItem;
            newItem->next = op2->next;
            op2->next->previous = newItem;
        }
    }
    free(item);
    free(op1);
    free(op2);
}

char *calculateResult(LinkedList *expression)
{

    LinkedList *tmp = expression;

    if (isValidInfixExpression(tmp))
    {
        int *aux = getMaxWeight(tmp);

        while (*(aux + 1) > 1)
        {
            updateState(&tmp, *aux);
            aux = getMaxWeight(tmp);
        }

        Stack *operandStack = createStack();
        Stack *operatorStack = createStack();

        LinkedListNode *head = tmp->head;

        while (head)
        {
            if (isNumber(head->data))
                pushStack(operandStack, head->data);
            else
                pushStack(operatorStack, head->data);

            head = head->next;
        }

        free(tmp);

        double result = convertToDouble(popStack(operandStack));

        while (!isEmptyStack(*operatorStack))
        {
            char *op = popStack(operatorStack);
            double nextOperand = convertToDouble(popStack(operandStack));

            if (!strcmp(op, "+"))
                result += nextOperand;
            else if (!strcmp(op, "-"))
                result -= nextOperand;
        }

        free(operandStack);
        free(operatorStack);

        char *r  = (char *)malloc(20 * sizeof(char));

        sprintf(r, "%.1f", result);
        return r;//r;
    }
    else
        return "INVALID OPERATION";
}