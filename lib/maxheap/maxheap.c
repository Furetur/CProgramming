#include <stdlib.h>
#include "maxheap.h"

#include "../arrayutils/arrayutils.h"
#include "../commonutils/commonutils.h"


MaxHeap* maxHeapInit(const int size)
{
    MaxHeap* maxHeap = malloc(sizeof(MaxHeap));
    maxHeap->tree = createIntArray(size);
    maxHeap->maxSize = size;
    maxHeap->heapSize = 0;
    return maxHeap;
}


void deleteMaxHeap(MaxHeap* maxHeap)
{
    free(maxHeap->tree);
    free(maxHeap);
}


int maxHeapGetValue(const MaxHeap* maxHeap, const int index)
{
    return maxHeap->tree[index];
}


void maxHeapSwap(const MaxHeap* maxHeap, const int index1, const int index2)
{
    swapInts(&maxHeap->tree[index1], &maxHeap->tree[index2]);
}


int parent(int i)
{
    if (i == 0)
    {
        return 0;
    }
    return (i - 1) / 2;
}


int leftChild(int i)
{
    return 2 * i + 1;
}


int rightChild(int i)
{
    return 2 * i + 2;
}


bool leftChildExists(const MaxHeap* maxHeap, const int i)
{
    return leftChild(i) < maxHeap->heapSize;
}


bool rightChildExists(const MaxHeap* maxHeap, const int i)
{
    return rightChild(i) < maxHeap->heapSize;
}


void maxHeapUp(MaxHeap* maxHeap, const int index)
{
    if (parent(index) == index)
    {
        return;
    }
    const int parentValue = maxHeapGetValue(maxHeap, parent(index));
    const int curValue = maxHeapGetValue(maxHeap, index);
    if (parentValue >= curValue)
    {
        return;
    }
    maxHeapSwap(maxHeap, parent(index), index);
    maxHeapUp(maxHeap, parent(index));
}


void maxHeapDown(MaxHeap* maxHeap, const int index)
{
    if (!leftChildExists(maxHeap, index))
    {
        return;
    }

    const int left = leftChild(index);
    const int right = rightChild(index);

    int maxValue = maxHeapGetValue(maxHeap, index);
    int largestChildIndex = index;

    if (leftChildExists(maxHeap, index) && maxHeapGetValue(maxHeap, left) > maxValue)
    {
        largestChildIndex = left;
        maxValue = maxHeapGetValue(maxHeap, left);
    }
    if (rightChildExists(maxHeap, index) && maxHeapGetValue(maxHeap, right) > maxValue)
    {
        largestChildIndex = right;
    }

    if (largestChildIndex == index)
    {
        return;
    }

    maxHeapSwap(maxHeap, index, largestChildIndex);
    maxHeapDown(maxHeap, largestChildIndex);
}


void maxHeapAdd(MaxHeap* maxHeap, const int value)
{
    if (maxHeap->heapSize == maxHeap->maxSize)
    {
        return;
    }

    maxHeap->tree[maxHeap->heapSize] = value;
    maxHeapUp(maxHeap, maxHeap->heapSize);
    maxHeap->heapSize += 1;
}


int maxHeapPop(MaxHeap* maxHeap)
{
    const int result = maxHeapGetValue(maxHeap, 0);
    maxHeapSwap(maxHeap, 0, maxHeap->heapSize - 1);
    maxHeap->heapSize -= 1;
    maxHeapDown(maxHeap, 0);
    return result;
}


void maxHeapBuild(MaxHeap* maxHeap, const int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        maxHeap->tree[i] = arr[i];
    }
    maxHeap->heapSize = size;
    for (int i = size / 2; i >= 0; i--)
    {
        maxHeapDown(maxHeap, i);
    }
}
