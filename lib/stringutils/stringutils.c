//
// Created by furet on 26.02.2020.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../arrayutils/arrayutils.h"


int countSubstringOccurrences(const char* parentString, const int parentLength,
        const char* childString, const int childLength)
{
    if (parentLength < childLength)
    {
        return 0;
    }

    int counter = 0;
    for (int leftIndex = 0; leftIndex <= parentLength - childLength; ++leftIndex)
    {
        char* parentSubstring = getSubarray(parentString, leftIndex, leftIndex + parentLength - 1);
        if (areArraysEqual(parentSubstring, childString, childLength))
        {
            counter++;
        }
    }
    return counter;
}


int* countCharOccurrences(const char* str)
{
    int* charOccurrences = createIntArray(256);

    for (int charNum = 0; charNum < strlen(str); charNum++)
    {
        const char curSymbol = str[charNum];
        charOccurrences[curSymbol]++;
    }

    return charOccurrences;
}


int getDigitFromSymbol(const char symbol)
{
    return (int) (symbol - '0');
}


bool isSymbolMathOperator(const char symbol)
{
    return symbol == '+' || symbol == '*' || symbol == '/' || symbol == '-';
}


bool isInteger(char* string)
{
    const int length = strlen(string);

    for (int i = 0; i < length; ++i)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }
    return true;
}


long long hashCode(char* string, const int prime, const int modulo)
{
    const unsigned long length = strlen(string);
    int primeRaisedToThePower = 1;
    long long result = 0;

    for (int i = 0; i < length; ++i)
    {
        result += (primeRaisedToThePower * ((int) string[i])) % modulo;
        primeRaisedToThePower = (primeRaisedToThePower * prime) % modulo;
    }
    return  result;
}


int integerFromString(char* string)
{
    const int stringLength = (int) strlen(string);
    int result = 0;

    for (int i = 0; i < stringLength; ++i)
    {
        const int curDigit = getDigitFromSymbol(string[i]);
        result = result * 10 + curDigit;
    }
    return result;
}


// supports only ( and ) parenthesis
bool isBalanced(const char str[])
{
    const int length = strlen(str);

    int counter = 0;
    for (int i = 0; i < length; ++i)
    {
        if (str[i] == '(')
        {
            counter++;
        }
        if (str[i] == ')')
        {
            counter--;
        }
        if (counter < 0)
        {
            return false;
        }
    }
    return counter == 0;
}
