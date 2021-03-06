//
// Created by furetur on 07.03.2020.
//


#include <stdlib.h>
#include "../lib/expressions/expressions.h"
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/stringutils/stringutils.h"
#include "stdio.h"

const int EXPRESSION_MAX_SIZE = 500;


int main()
{
    char* infixExpression = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter an expression in the infix form:\n");
    scanf("%[^\n]", infixExpression);

    if (!isBalanced(infixExpression))
    {
        printf("Wrong combination of parenthesis");
        free(infixExpression);
        return 0;
    }

    char* postfixExpression = convertInfixToPostfix(infixExpression);

    bool isValid = isPostfixExpressionValid(postfixExpression);

    if (isValid)
    {
        printf("Your expression in the postfix form: %s\n", postfixExpression);
    }
    else
    {
        printf("The expression you entered is not valid");
    }

    free(infixExpression);
    free(postfixExpression);

    return 0;
}