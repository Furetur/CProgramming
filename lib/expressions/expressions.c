//
// Created by furetur on 07.03.2020.
//

#include <stddef.h>
#include <ctype.h>
#include "../stack/stack.h"
#include "../stringutils/stringutils.h"
#include "../arrayutils/arrayutils.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"


const int OPERATORS_NUM = 5;
const char operatorIds[5] = {'+', '-', '*', '/', '('};
const int operatorPrecedence[5] = {2, 2, 3, 3, 1};


char** createTokensArray(const int length)
{
    char** tokens = malloc(length * sizeof(char*));

    for (int i = 0; i < length; ++i)
    {
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
    if (isdigit(symbol))
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

    for (int i = 0; i < length; ++i)
    {
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


void freeTokens(char** tokens, int tokensNumberUpperBound)
{
    for (int i = 0; i < tokensNumberUpperBound; ++i)
    {
        if (tokens[i] == NULL)
        {
            break;
        }
        free(tokens[i]);
    }
    free(tokens);
}


bool isPostfixExpressionValid(char expression[])
{
    int length = strlen(expression);
    char** tokens = parseIntoTokens(expression);
    int counter = 0;
    for (int i = 0; i < length; ++i)
    {
        char* curToken = tokens[i];
        if (curToken == NULL)
        {
            break;
        }
        if (isInteger(curToken))
        {
            counter += 1;
        }
        else if (strlen(curToken) == 1 && isSymbolMathOperator(curToken[0]))
        {
            if (counter < 2)
            {
                freeTokens(tokens, length);
                return false;
            }
            counter -= 1;
        }
        else
        {
            freeTokens(tokens, length);
            return false;
        }
    }
    freeTokens(tokens, length);
    return counter == 1;
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
            }
            else if (curToken[0] == '*')
            {
                result = operand1 * operand2;
            }
            else if (curToken[0] == '-')
            {
                result = operand1 - operand2;
            }
            else if (curToken[0] == '/')
            {
                if (operand2 == 0)
                {
                    // division by zero
                    errno = 22;
                    break;
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
    freeTokens(tokens, expressionLength);
    return result;
}


int getOperatorId(const char operator)
{
    for (int i = 0; i < OPERATORS_NUM; ++i)
    {
        if (operatorIds[i] == operator)
        {
            return i;
        }
    }
    return -1;
}


char* convertInfixToPostfix(char* expression)
{
    const int expressionLength = strlen(expression);
    char** tokens = parseIntoTokens(expression);

    Stack* operatorStack = newStack();

    char* postfixExpression = createCharArray(expressionLength * 2 + 1);
    int postfixExpressionIndex = 0;

    for (int i = 0; i < expressionLength; ++i)
    {
        char* curToken = tokens[i];

        // break if all the tokens have been read
        if (curToken == NULL)
        {
            break;
        }

        const int curTokenLength = strlen(curToken);

        if (isInteger(curToken))
        {
            // write the number to the output

            // if it not the beginning of the string then add a whitespace
            if (postfixExpressionIndex != 0)
            {
                postfixExpression[postfixExpressionIndex] = ' ';
                postfixExpressionIndex++;
            }
            // write the number into the array
            writeCharArrayIntoArray(postfixExpression, curToken, postfixExpressionIndex);
            // increment the index
            postfixExpressionIndex += curTokenLength;
            continue;
        }
        if (curTokenLength != 1)
        {
            // exception
            continue;
        }
        if (curToken[0] == '(')
        {
            // add ( to the stack
            stackPush(operatorStack, getOperatorId('('));
            continue;
        }
        if (curToken[0] == ')')
        {
            int topOperator = stackPop(operatorStack);
            // pop all operators that are not (
            while (topOperator != getOperatorId('('))
            {
                // add a whitespace
                postfixExpression[postfixExpressionIndex] = ' ';
                postfixExpressionIndex++;
                // write operator to the output
                postfixExpression[postfixExpressionIndex] = operatorIds[topOperator];
                postfixExpressionIndex++;
                // pop the operator from stack
                topOperator = stackPop(operatorStack);
            }
            continue;
        }
        // if symbol is one of + - * /
        if (isSymbolMathOperator(curToken[0]))
        {
            const int curOperatorId = getOperatorId(curToken[0]);
            const int curOperatorPrecedence = operatorPrecedence[curOperatorId];

            // pop all operators that are more important than the current operator
            while (operatorStack->size > 0 && operatorPrecedence[stackPeek(operatorStack)] > curOperatorPrecedence)
            {
                // write operator to the output
                const int topOperatorId = stackPop(operatorStack);
                const char topOperator = operatorIds[topOperatorId];
                // write a whitespace
                postfixExpression[postfixExpressionIndex] = ' ';
                postfixExpressionIndex++;
                // write the topOperator
                postfixExpression[postfixExpressionIndex] = topOperator;
                postfixExpressionIndex++;
            }
            stackPush(operatorStack, curOperatorId);
        }
    }

    // if the stack is not empty
    while (operatorStack->size > 0)
    {
        const int operatorId = stackPop(operatorStack);
        const char operator = operatorIds[operatorId];

        // write a whitespace
        postfixExpression[postfixExpressionIndex] = ' ';
        postfixExpressionIndex++;
        // write the top operator from stack
        postfixExpression[postfixExpressionIndex] = operator;
        postfixExpressionIndex++;
    }

    // delete stack
    deleteStack(operatorStack);
    // delete tokens
    freeTokens(tokens, expressionLength);

    return postfixExpression;
}
