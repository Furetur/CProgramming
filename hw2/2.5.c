#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/stringutils/stringutils.h"


const int MAX_STRING_SIZE = 200;
const int NUMBER_OF_CHARS = 256;


int main()
{
    char* str1 = createCharArray(MAX_STRING_SIZE);
    char* str2 = createCharArray(MAX_STRING_SIZE);

    printf("Enter the first string:\n");
    scanf("%s", str1);

    printf("Enter the second string:\n");
    scanf("%s", str2);

    int* charOccurrences1 = countCharOccurrences(str1);
    int* charOccurrences2 = countCharOccurrences(str2);

    if (areIntArraysEqual(charOccurrences1, charOccurrences2, NUMBER_OF_CHARS))
    {
        printf("The first string CAN be obtained from the second string by swapping the characters");
    } else
    {
        printf("The first string CANNOT be obtained from the second string by swapping the characters");
    }

    free(str1);
    free(str2);
    free(charOccurrences1);
    free(charOccurrences2);

    return 0;
}
