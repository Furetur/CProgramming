#include "math.h"
#include "../arrayutils/arrayutils.h"


int getNumberOfDigits(const int num)
{
    int counter = 0;
    int remainder = num;
    while (remainder > 0)
    {
        remainder /= 10;
        counter++;
    }
    return counter;
}

int* getDigits(const int num)
{
    const int numberOfDigits = getNumberOfDigits(num);
    int* digits = createIntArray(numberOfDigits);

    int remainder = num;

    for (int i = 0; i < numberOfDigits; i++)
    {
        const int curDigit = remainder % 10;
        digits[i] = curDigit;
        remainder /= 10;
    }

    return digits;
}


int* countDigitOccurrences(const int* digits, const int size)
{
    int* digitOccurrences = createIntArray(10);

    for (int i = 0; i < size; i++)
    {
        const int curDigit = digits[i];
        digitOccurrences[curDigit]++;
    }

    return digitOccurrences;
}


bool isPrime(const int number)
{
    for (int i = 2; i < number - 1; ++i)
    {
        if ((number % i) == 0)
        {
            return false;
        }
    }
    return true;
}


int nextPrime(const int number)
{
    int curNumber = number + 1;
    while (!isPrime(curNumber))
    {
        curNumber++;
    }
    return curNumber;
}
