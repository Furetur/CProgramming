//
// Created by furet on 26.02.2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "arrayutils.h"


void fillCharArray(char* array, const int size, const char val)
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = (char) val;
    }
}


void emptyCharArray(char* array, const int size)
{
    fillCharArray(array, size, (char) 0);
}


// Array creators

char* createCharArrayWithVal(const int size, const char defaultVal)
{
    char* arr = calloc(size, sizeof(char));
    fillCharArray(arr, size, defaultVal);
    return arr;
}

char* createCharArray(const int size)
{
    return createCharArrayWithVal(size, (char) 0);
}


int* createIntArrayWithVal(const int size, const int defaultVal)
{
    int* arr = calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        arr[i] = defaultVal;
    }
    return arr;
}


int* createIntArray(const int size)
{
    return createIntArrayWithVal(size, 0);
}


bool* createBoolArrayWithVal(const int size, const bool val)
{
    bool* arr = calloc(size, sizeof(bool));
    for (int i = 0; i < size; ++i)
    {
        arr[i] = val;
    }
    return arr;
}


bool* createBoolArray(const int size)
{
    return createBoolArrayWithVal(size, true);
}

//2d array creators


int** createInt2dArrayWithVal(const int numRows, const int numCols, const int val)
{
    int** arr = (int**) calloc(numRows, sizeof(int*));

    for (int i = 0; i < numRows; i++)
    {
        arr[i] = createIntArrayWithVal(numCols, val);
    }
    return arr;
}


int** createInt2dArray(const int numRows, const int numCols)
{
    return createInt2dArrayWithVal(numRows, numCols, 0);
}


bool** createBool2dArrayWithVal(const int numRows, const int numCols, const bool val)
{
    bool** arr = (bool**) calloc(numRows, sizeof(bool*));

    for (int i = 0; i < numRows; i++)
    {
        arr[i] = createBoolArrayWithVal(numCols, val);
    }
    return arr;
}


bool** createBool2dArray(const int numRows, const int numCols)
{
    return createBool2dArrayWithVal(numRows, numCols, true);
}


void freeInt2dArray(int** array, const int numRows)
{
    for (int i = 0; i < numRows; ++i)
    {
        free(array[i]);
    }
    free(array);
}


void freeBool2dArray(bool** array, const int numRows)
{
    for (int i = 0; i < numRows; ++i)
    {
        free(array[i]);
    }
    free(array);
}


// Array IO


void readIntArray(int arr[], const int size)
{
    printf("Enter your array with whitespaces separating elements:\n");
    for (int i = 0; i < size; ++i)
    {
        scanf("%d", &arr[i]);
    }
}


void readInt2dArray(int** arr, const int numRows, const int numCols)
{
    for (int i = 0; i < numRows; i++)
    {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < numCols; j++)
        {

            scanf("%d", &arr[i][j]);
        }
        printf("\n");
    }
}


void printIntArray(const int arr[], const int size)
{
    printf("Updated array:\n");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Array functions


void emptyIntArray(int arr[], const int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = 0;
    }
}


void writeCharArrayIntoArray(char* parentArray, char* childArray, int parentArrayStartIndex)
{
    for (int i = 0; i < strlen(childArray); ++i) {
        parentArray[i + parentArrayStartIndex] = childArray[i];
    }
}


char* copyCharArray(char* array)
{
    const int length = strlen(array);
    char* destination = createCharArray(length + 1);
    for (int i = 0; i < length; ++i) {
        destination[i] = array[i];
    }
    return destination;
}


void reverseIntArray(int arr[], const int start, const int end)
{
    int left = start;
    int right = end;
    while (left < right)
    {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}


bool areArraysEqual(const char* arr1, const char* arr2, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}


char* getSubarray(const char* array, const int start, const int end)
{
    char* subarray = createCharArray(end - start + 1);
    for (int i = start; i <= end; ++i)
    {
        subarray[i - start] = array[i];
    }
    return subarray;
}


int* copyIntArray(const int* array, const int size)
{
    int* newArr = createIntArray(size);
    for (int i = 0; i < size; i++)
    {
        newArr[i] = array[i];
    }

    return newArr;
}



// Quick sort


int partitionArray(int* arr, const int startIndex, const int endIndex)
{
    const int pivotIndex = endIndex;
    const int pivot = arr[pivotIndex];

    int leftElementGreaterOrEqualThanPivotIndex = startIndex;

    for (int curIndex = startIndex; curIndex < pivotIndex; curIndex++)
    {
        const int curElement = arr[curIndex];
        if (curElement < pivot)
        {
            // swap
            int temp = curElement;
            arr[curIndex] = arr[leftElementGreaterOrEqualThanPivotIndex];
            arr[leftElementGreaterOrEqualThanPivotIndex] = temp;
            leftElementGreaterOrEqualThanPivotIndex++;
        }
    }
    // swap pivot with the first element that is >= than pivot
    arr[pivotIndex] = arr[leftElementGreaterOrEqualThanPivotIndex];
    arr[leftElementGreaterOrEqualThanPivotIndex] = pivot;
    return leftElementGreaterOrEqualThanPivotIndex;
}


void quickSort(int* arr, const int startIndex, const int endIndex)
{
    if (startIndex >= endIndex)
    {
        return;
    }
    // arr[pivotIndex] is at a correct position
    int pivotIndex = partitionArray(arr, startIndex, endIndex);
    quickSort(arr, startIndex, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, endIndex);
}


bool allTruthy(const bool* arr, const int size)
{
    for (int i = 0; i < size; ++i) {
        if (!arr[i])
        {
            return false;
        }
    }
    return true;
}


bool allFalsy(const bool* arr, const int size)
{
    for (int i = 0; i < size; ++i) {
        if (arr[i])
        {
            return false;
        }
    }
    return true;
}


int findFirstInBoolArray(const bool* arr, const bool val, const int size)
{
    for (int i = 0; i < size; ++i) {
        if (arr[i] == val)
        {
            return i;
        }
    }
    return -1;
}
