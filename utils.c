#include "queue.c"

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

char *compute(const char *expression)
{
    Queue operandQueue = create();
    Queue operatorQueue = create();

    while (*expression != '\0')
    {
        if (isdigit(*expression))
            push(&operandQueue, *expression);
        else
            push(&operatorQueue, *expression);

        expression++;
    }

    float result = 0;

    while (!empty(operatorQueue))
    {
        char operator= pop(&operatorQueue);
        int operand2 = pop(&operandQueue) - '0';
        int operand1 = pop(&operandQueue) - '0';
        if (operator== '+')
            result = operand1 + operand2;
        if (operator== '-')
            result = operand1 - operand2;
        if (operator== '*')
            result = operand1 * operand2;
        else
        {
            if (operand2 == 0)
                result = 0;
            else
                result = operand1 / operand2;
        }
    }
}