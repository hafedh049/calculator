#include "stack.c"

const char *labels[16] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "+",
    "-",
    "x",
    "/",
    "C",
    "=",
};

const int positions[16][4] = {
    {0, 5, 3, 1},
    {0, 4, 1, 1},
    {1, 4, 1, 1},
    {2, 4, 1, 1},
    {0, 3, 1, 1},
    {1, 3, 1, 1},
    {2, 3, 1, 1},
    {0, 2, 1, 1},
    {1, 2, 1, 1},
    {2, 2, 1, 1},
    {3, 4, 1, 1},
    {3, 3, 1, 1},
    {3, 2, 1, 1},
    {3, 1, 1, 1},
    {0, 1, 3, 1},
    {0, 0, 0, 0},
};

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int isDigit(char ch)
{
    return isdigit(ch);
}

char *evaluateInfixExpression(const char *infix)
{
    Node *operandStack;
    Node *operatorStack;

    while (*infix != '\0')
    {
        if (isdigit(*infix))
        {
            int operand = *infix;
            push(&operandStack, operand); // Convert operand to char
        }
        else if (isOperator(*infix))
            push(&operatorStack, *infix);
        else if (*infix == '(')
            push(&operatorStack, *infix);
        else if (*infix == ')')
        {
            while (operatorStack.top != NULL && operatorStack.top->data != '(')
            {
                char operator= pop(&operatorStack);
                char operand2 = pop(&operandStack);
                char operand1 = pop(&operandStack);
                char result[3];
                result[0] = operand1;
                result[1] = operator;
                result[2] = operand2;
                result[3] = '\0';
                push(&operandStack, *result);
            }
            // Pop '(' from the operator stack
            pop(&operatorStack);
        }
        infix++;
    }

    // Process remaining operators in the stacks
    while (operatorStack.top != NULL)
    {
        char operator= pop(&operatorStack);
        char operand2 = pop(&operandStack);
        char operand1 = pop(&operandStack);
        char result[3];
        result[0] = operand1;
        result[1] = operator;
        result[2] = operand2;
        result[3] = '\0';
        push(&operandStack, *result);
    }

    // The final result is on the operand stack
    return operandStack.top != NULL ? operandStack.top : NULL;
}