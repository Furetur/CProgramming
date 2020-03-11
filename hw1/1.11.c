#include <stdio.h>
#include <stdlib.h>
#include "../lib/arrayutils/arrayutils.h"


int main()
{
    int length = 0;

    printf("Enter the length or your array:\n");
    scanf("%d", &length);

    int *arr = createIntArray(length);
    readIntArray(arr, length);

    quickSort(arr, 0, length - 1);

    printIntArray(arr, length);

    free(arr);

    return 0;
}