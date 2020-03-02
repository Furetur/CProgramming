//
// Created by furet on 27.02.2020.
//


#include "../maxheap/maxheap.h"


void heapSort(int arr[], const int size)
{
    MaxHeap* maxHeap = maxHeapInit(size);
    maxHeapBuild(maxHeap, arr, size);

    for (int i = size - 1; i >= 0; i--)
    {
        arr[i] = maxHeapPop(maxHeap);
    }

    deleteMaxHeap(maxHeap);
}



