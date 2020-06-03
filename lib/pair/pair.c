//
// Created by furetur on 13.03.2020.
//

#include "pair.h"
#include "../arrayutils/arrayutils.h"
#include "stdlib.h"


void swapIntPairs(IntPair* pair1, IntPair* pair2)
{
    IntPair temp = *pair1;
    *pair1 = *pair2;
    *pair2 = temp;
}

IntPair* convertIntArrayIntoPairs(const int* arr, const int size)
{
    IntPair* pairs = calloc(sizeof(IntPair), size);

    for (int i = 0; i < size; ++i)
    {
        pairs[i] = (IntPair) {arr[i], i};
    }
    return pairs;
}


// Quick sort pairs

int partitionPairsArray(IntPair* arr, const int startIndex, const int endIndex)
{
    const int pivotIndex = endIndex;
    const IntPair pivot = arr[pivotIndex];

    int leftElementGreaterOrEqualThanPivotIndex = startIndex;

    for (int curIndex = startIndex; curIndex < pivotIndex; curIndex++)
    {
        const IntPair curElement = arr[curIndex];
        if (curElement.first < pivot.first)
        {
            // swap
            swapIntPairs(&arr[curIndex], &arr[leftElementGreaterOrEqualThanPivotIndex]);
            leftElementGreaterOrEqualThanPivotIndex++;
        }
    }
    // swap pivot with the first element that is >= than pivot
    swapIntPairs(&arr[pivotIndex], &arr[leftElementGreaterOrEqualThanPivotIndex]);
    return leftElementGreaterOrEqualThanPivotIndex;
}


void quickSortIntPairs(IntPair* arr, const int startIndex, const int endIndex)
{
    if (startIndex >= endIndex)
    {
        return;
    }
    // arr[pivotIndex] is at a correct position
    int pivotIndex = partitionPairsArray(arr, startIndex, endIndex);
    quickSortIntPairs(arr, startIndex, pivotIndex - 1);
    quickSortIntPairs(arr, pivotIndex + 1, endIndex);
}


int* sortIndexesByValues(int* arr, const int size)
{
    int* sortedIndexes = createIntArray(size);

    IntPair* pairs = convertIntArrayIntoPairs(arr, size);

    quickSortIntPairs(pairs, 0, size - 1);

    for (int i = 0; i < size; ++i)
    {
        sortedIndexes[i] = pairs[i].second;
    }

    free(pairs);
    return sortedIndexes;
}