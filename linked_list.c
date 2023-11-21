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

void appendLinkedList(LinkedList *list, char *item)
{
    LinkedListNode *linkedListNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    linkedListNode->data = item;
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

char *popLinkedList(LinkedList *list, char *item)
{
    assert(!isEmptyLinkedList(*list));

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

char *getLinkedList(LinkedList *list, int index)
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
    return head->data;
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

int isNumber(char *num)
{
    char *endPtr;

    strtod(num, &endPtr);

    if (endPtr == num || *endPtr != '\0')
        return 0;

    if (num[0] == '-' && isdigit(num[1]))
        return 1;

    return 0;
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
        else if ((!isNumber(prev->data) && current == NULL) || (isNumber(prev->data) && isNumber(current->data)) || ((!isNumber(prev->data) && !isNumber(current->data))))
            return 0;
    }

    return 1;
}

int *getMaxWeight(LinkedList *expression)
{

    int indx = 0, max = 0;
    LinkedListNode *head = expression->head;

    int *aux = (int *)malloc(2 * sizeof(int));

    while (head)
    {
        if (head->weight == 2)
        {
            aux[0] = indx;
            aux[1] = 2;
            return aux;
        }

        else if (head->weight > max)
            max = head->weight;
        head = head->next;
    }

    aux[0] = indx;
    aux[1] = max;

    return aux;
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

    double res = 0;

    if (!strcmp(item->data, "*"))
        res = convertToDouble(item->previous->data) * convertToDouble(item->next->data);
    else
        res = convertToDouble(item->previous->data) / convertToDouble(item->next->data);

    item->data = "";

    sprintf(item->data, "%.1f", res);

    LinkedListNode *op1 = item->previous;
    LinkedListNode *op2 = item->next;

    if (op1->previous == NULL && op2->next == NULL)
    {
        item->next = NULL;
        item->previous = NULL;
        (*expression)->head = item;
        free(op1);
        free(op2);
    }
    else
    {
        if (op1->previous == NULL)
        {
            (*expression)->head = item;
            item->previous = NULL;
            item->next = op2->next;
            op2->next->previous = item;
            free(op1);
            free(op2);
        }
        else if (op2->next == NULL)
        {
            op1->previous->next = item;
            item->previous = op1->previous;
            item->next = NULL;
            free(op2);
            free(op1);
        }
        else
        {
            item->previous = op1->previous;
            op1->previous->next = item;
            item->next = op2->next;
            op2->next->previous = item;
            free(op2);
            free(op1);
        }
    }
}

char *calculateResult(LinkedList *expression)
{

    LinkedList *tmp = expression;

    if (isValidInfixExpression(tmp))
    {

        double result = 0;

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

        result = convertToDouble(popStack(operandStack));
        while (!isEmptyStack(*operatorStack))
        {
            char *op = popStack(operatorStack);
            double nextOperand = convertToDouble(popStack(operandStack));

            if (!strcmp(op,"+"))
                result += nextOperand;
            else if (!strcmp(op,"-"))
                result -= nextOperand;
        }

        free(operandStack);
        free(operatorStack);

        char *r;

        sprintf(r,"%.1f",result);

        return r;
    }
    else
        return "INVALID OPERATION";
}