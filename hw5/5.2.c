//
// Created by furetur on 06.03.2020.
//
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/expressions/expressions.h"


const int EXPRESSION_MAX_SIZE = 500;


int main()
{
    char* postfixExpression = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter the expression in the postfix form:\n");
    scanf("%[^\n]", postfixExpression);

    if (isPostfixExpressionValid(postfixExpression))
    {
        const int result = evaluatePostfixExpression(postfixExpression);
        if (errno == 22)
        {
            printf("You tried to divide by zero -_-");
        }
        else
        {
            printf("Evaluation result: %d\n", result);
        }
    }
    else
    {
        printf("The expression you entered is not valid");
    }

    free(postfixExpression);
    return 0;
}