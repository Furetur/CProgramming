//
// Created by furetur on 13.03.2020.
//

#ifndef HOMEWORK_PAIR_H
#define HOMEWORK_PAIR_H

typedef struct IntPair
{
    int first;
    int second;
} IntPair;

void quickSortIntPairs(IntPair* arr, int startIndex, int endIndex);

int* sortIndexesByValues(int* arr, int size);

#endif //HOMEWORK_PAIR_H
