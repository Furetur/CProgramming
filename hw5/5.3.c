//
// Created by furetur on 07.03.2020.
//

#include <stdlib.h>
#include <errno.h>
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/expressions/expressions.h"
#include "stdio.h"
#include "../lib/stringutils/stringutils.h"

const int EXPRESSION_MAX_SIZE = 500;

void tryToEvaluatePostfixExpression(char* postfixExpression)
{
    if(!isPostfixExpressionValid(postfixExpression))
    {
        printf("The expression you entered is not valid");
        return;
    }

    printf("Your expression in the postfix form: %s\n", postfixExpression);
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

int main()
{
    char* infixExpression = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter the expression in the infix form (please do not use whitespaces):\n");
    scanf("%[^\n]", infixExpression);

    if (!isBalanced(infixExpression))
    {
        printf("Wrong combination of parenthesis");
        free(infixExpression);
        return 0;
    }

    char* postfixExpression = convertInfixToPostfix(infixExpression);

    tryToEvaluatePostfixExpression(postfixExpression);

    free(postfixExpression);
    free(infixExpression);
    return 0;
}
