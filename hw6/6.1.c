//
// Created by furetur on 09.03.2020.
//

#include <stdbool.h>
#include "stdio.h"
#include "../lib/arrayutils/arrayutils.h"
#include "stdlib.h"


bool* getBits(char byte)
{
    bool* bits = createBoolArrayWithVal(8, false);

    char shiftedByte = byte;
    for (int i = 0; i < 8; ++i)
    {
        bits[i] = (bool) (shiftedByte & 1);
        shiftedByte = shiftedByte >> 1;
    }
    return bits;
}


bool* getBitsFromDouble(double number)
{
    bool* bits = createBoolArrayWithVal(64, 0);

    unsigned char* bytes = (unsigned char*) &number;

    for (int i = 0; i < 8; ++i)
    {
        char byte = bytes[i];
        bool* curBits = getBits(byte);
        for (int j = 0; j < 8; ++j)
        {
            bits[8 * i + j] = curBits[j];
        }
        free(curBits);
    }

    return bits;
}


void splitDoubleBits(bool* bits, bool* signBit, bool* exponentBits, bool* mantissaBits)
{
    for (int i = 0; i < 52; ++i)
    {
        mantissaBits[i] = bits[i];
    }

    for (int i = 52; i < 63; ++i)
    {
        exponentBits[i - 52] = bits[i];
    }

    *signBit = bits[63];
}


double getMantissaFromBits(bool* mantissaBits)
{
    double mantissa = 1;

    long long powerOfTwo = 2;

    for (int i = 51; i >= 0; --i)
    {
        mantissa += mantissaBits[i] * (((double) 1 ) / powerOfTwo);
        powerOfTwo *= 2;
    }
    return mantissa;
}


int getExponentFromBits(bool* exponentBits)
{
    int exponent = 0;

    for (int i = 10; i >= 0; --i)
    {
        exponent *= 2;
        exponent += exponentBits[i];
    }

    return exponent - 1023;
}


char getSignChar(bool sign)
{
    if (sign == true)
    {
        return '-';
    }
    return '+';
}


int main()
{
    char* inputString = createCharArray(100);

    printf("Enter your number:\n");
    scanf("%s", inputString);

    double inputNumber = strtod(inputString, NULL);

    bool* doubleBits = getBitsFromDouble(inputNumber);

    bool* mantissaBits = createBoolArrayWithVal(52, 0);
    bool* exponentBits = createBoolArrayWithVal(11, 0);
    bool signBit = false;

    splitDoubleBits(doubleBits, &signBit, exponentBits, mantissaBits);

    printf("How your number is represented in the computer:\n");
    printf("%c%.10f * 2 ^ (%d)",
           getSignChar(signBit),
           getMantissaFromBits(mantissaBits),
           getExponentFromBits(exponentBits));



    free(inputString);
    free(doubleBits);
    free(mantissaBits);
    free(exponentBits);

    return 0;
}