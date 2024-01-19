#include "queue.c"

const char *labels[14] = {
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
    "C",
    "=",
};

const int positions[14][4] = {
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
    {3, 1, 1, 2},
    {3, 3, 1, 2},
    {0, 1, 3, 1},
    {3, 5, 1, 1},
};

// Function to check if a character is an operator (+, -, *, /)
int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*';
}

// Function to evaluate an expression using the Shunting Yard algorithm
char *compute(const char *expression)
{
    Queue plusQueue = create();
    Queue minusQueue = create();

    int result = 0;

    while (*expression != '\0')
    {
        if (!isOperator(*expression))
            push(&plusQueue, *expression - '0');
        else
        {
            if (*expression == '-')
            {
                expression++;
                int operand = *expression - '0';
                push(&minusQueue, operand);
            }
        }
        expression++;
    }

    while (!empty(plusQueue))
        result += pop(&plusQueue);

    while (!empty(minusQueue))
        result -= pop(&minusQueue);

    char *target = (char *)malloc(sizeof(char) * ((int)log10(fabs(result)) + 1) + 1);

    sprintf(target, "%d", result);
    return target;
}

const char *concatenate(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int totalLength = len1 + len2;

    char *result = (char *)malloc((totalLength + 1) * sizeof(char));

    strcpy(result, str1);

    strcat(result, str2);

    return result;
}