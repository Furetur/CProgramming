//
// Created by furet on 26.02.2020.
//

#include <stdbool.h>

#ifndef HOMEWORK_NUMBERUTILS_H
#define HOMEWORK_NUMBERUTILS_H


int getNumberOfDigits(int num);

int* getDigits(int num);

int* countDigitOccurrences(const int* digits, int size);

bool isPrime(int number);

int nextPrime(int number);

#endif //HOMEWORK_NUMBERUTILS_H
