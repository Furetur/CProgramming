//
// Created by furetur on 07.03.2020.
//


#include <stdlib.h>
#include "../lib/expressions/expressions.h"
#include "../lib/arrayutils/arrayutils.h"
#include "stdio.h"

const int EXPRESSION_MAX_SIZE = 500;


int main()
{
    char* infixExpression = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter an expression in the infix form:\n");
    scanf("%[^\n]", infixExpression);

    char* postfixExpression = convertInfixToPostfix(infixExpression);

    printf("Your expression in the postfix form: %s\n", postfixExpression);

    free(infixExpression);
    free(postfixExpression);

    return 0;
}