//
// Created by furetur on 06.03.2020.
//
#include "string.h"
#include "stdio.h"
#include "../lib/arrayutils/arrayutils.h"
#include "stdlib.h"
#include "../lib/stringutils/stringutils.h"
#include "../lib/stack/stack.h"
#include "../lib/expressions/expressions.h"


const int EXPRESSION_MAX_SIZE = 500;


int main()
{
    char* postfixExpression = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter the expression in the postfix form:\n");
    scanf("%[^\n]", postfixExpression);

    const int result = evaluatePostfixExpression(postfixExpression);

    printf("Evaluation result: %d\n", result);

    free(postfixExpression);
    return 0;
}