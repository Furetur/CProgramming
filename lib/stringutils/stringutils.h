//
// Created by furet on 26.02.2020.
//

#ifndef HOMEWORK_STRINGUTILS_H
#define HOMEWORK_STRINGUTILS_H


int countSubstringOccurrences(char* parentString, int parentLength, char* childString, int childLength);

int* countCharOccurrences(char* str);

long long hashCode(char* string, int prime, int modulo);

bool isInteger(char* string);

bool isSymbolMathOperator(char symbol);

int integerFromString(char* string);

bool isBalanced(const char str[]);

#endif //HOMEWORK_STRINGUTILS_H
