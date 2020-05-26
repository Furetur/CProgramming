//
// Created by furet on 26.02.2020.
//

#include "commonutils.h"


void swapInts(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}


int min(const int num1, const int num2)
{
    return num1 < num2 ? num1 : num2;
}


int max(const int num1, const int num2)
{
    return num1 > num2 ? num1 : num2;
}
