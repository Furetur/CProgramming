//
// Created by furetur on 07.03.2020.
//

#include <stddef.h>
#include "../stack/stack.h"
#include "../stringutils/stringutils.h"
#include "../arrayutils/arrayutils.h"
#include "stdlib.h"
#include "string.h"


char** createTokensArray(const int length)
{
    char** tokens = malloc(length * sizeof(char*));

    for (int i = 0; i < length; ++i) {
        tokens[i] = NULL;
    }
    return tokens;
}


int getTokenTypeBySymbol(char symbol)
{
    if (symbol == ' ')
    {
        // delimiter
        return 0;
    }
    if (isSymbolDigit(symbol))
    {
        // digit
        return 1;
    }
    if (symbol == '.')
    {
        // point in a number
        return 1;
    }
    if (isSymbolMathOperator(symbol) || symbol == '(' || symbol == ')')
    {
        // math operator
        return 2;
    }
    // exception
    return -1;
}


char** parseIntoTokens(char expression[])
{
    const int length = (int) strlen(expression);

    char** tokens = createTokensArray(length + 1);
    int curTokenIndex = -1;

    int curTokenType = -1;
    char* curToken = createCharArray(length + 1);
    int curTokenSymbolIndex = 0;

    for (int i = 0; i < length; ++i) {
        const char curChar = expression[i];
        const int curCharTokenType = getTokenTypeBySymbol(curChar);

        // if the pointer moved from one token to another
        // or if the pointer moved from one operator to another
        if ((curCharTokenType != curTokenType && curTokenType != 0) || (curTokenType == 2 && curCharTokenType == 2))
        {
            // if it wasn't the start of the string
            if (curTokenIndex != -1)
            {
                tokens[curTokenIndex] = copyCharArray(curToken);
                emptyCharArray(curToken, strlen(curToken));
            }
            curTokenIndex++;
            curTokenSymbolIndex = 0;
        }

        curTokenType = curCharTokenType;

        if (curCharTokenType == 0 || curCharTokenType == -1)
        {
            continue;
        }

        curToken[curTokenSymbolIndex] = curChar;
        curTokenSymbolIndex++;
    }

    // add the last token
    if (strlen(curToken) != 0)
    {
        tokens[curTokenIndex] = copyCharArray(curToken);
    }

    free(curToken);

    return tokens;
}


int evaluatePostfixExpression(char expression[])
{
    const int expressionLength = strlen(expression);

    char** tokens = parseIntoTokens(expression);

    Stack* stack = newStack();

    for (int i = 0; i < expressionLength; i++)
    {
        char* curToken = tokens[i];
        if (curToken == NULL)
        {
            break;
        }
        if (isInteger(curToken))
        {
            const int value = integerFromString(curToken);
            stackPush(stack, value);
            continue;
        }
        if (strlen(curToken) == 1 && isSymbolMathOperator(curToken[0]))
        {
            int operand2 = stackPop(stack);
            int operand1 = stackPop(stack);
            int result = 0;
            if (curToken[0] == '+')
            {
                result = operand1 + operand2;
            } else if (curToken[0] == '*')
            {
                result = operand1 * operand2;
            } else if (curToken[0] == '-')
            {
                result = operand1 - operand2;
            } else if (curToken[0] == '/')
            {
                if (operand2 == 0)
                {
                    // division by zero
                    return 0;
                }
                result = operand1 / operand2;
            }
            stackPush(stack, result);
            continue;
        }
        // exception
    }
    const int result = stackPop(stack);
    // free memory
    // delete stack
    deleteStack(stack);
    // delete tokens
    for (int i = 0; i < expressionLength; ++i) {
        if (tokens[i] == NULL)
        {
            break;
        }
        free(tokens[i]);
    }
    free(tokens);

    return result;
}

