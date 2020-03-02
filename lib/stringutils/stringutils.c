//
// Created by furet on 26.02.2020.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../arrayutils/arrayutils.h"


int countSubstringOccurrences(const char* parentString, const int parentLength, const char* childString, const int childLength)
{
    if (parentLength < childLength)
    {
        return 0;
    }

    int counter = 0;
    for (int leftIndex = 0; leftIndex <= parentLength - childLength; ++leftIndex) {
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
