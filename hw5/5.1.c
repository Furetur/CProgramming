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
    char* exp = createCharArray(EXPRESSION_MAX_SIZE);

    printf("Enter an expression in the infix form:\n");
    scanf("%[^\n]", exp);

    char* result = convertInfixToPostfix(exp);

    printf("Your expression in the postfix form: %s\n", result);

    free(exp);
    free(result);

    return 0;
}