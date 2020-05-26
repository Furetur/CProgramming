//
// Created by furetur on 07.03.2020.
//

#ifndef HOMEWORK_EXPRESSIONS_H
#define HOMEWORK_EXPRESSIONS_H


#include <stdbool.h>

bool areParenthesisBalanced(char* expression);

int evaluatePostfixExpression(char expression[]);

char* convertInfixToPostfix(char* expression);

bool isPostfixExpressionValid(char expression[]);

#endif //HOMEWORK_EXPRESSIONS_H
