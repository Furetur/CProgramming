#ifndef HOMEWORK_MAXHEAP_H
#define HOMEWORK_MAXHEAP_H


struct MaxHeap
{
    int* tree;
    int maxSize;
    int heapSize;
};

typedef struct MaxHeap MaxHeap;

MaxHeap* maxHeapInit(int size);

void deleteMaxHeap(MaxHeap* maxHeap);

int maxHeapGetValue(const MaxHeap* maxHeap, int index);

void maxHeapAdd(MaxHeap* maxHeap, int value);

int maxHeapPop(MaxHeap* maxHeap);

void maxHeapBuild(MaxHeap* maxHeap, const int arr[], int size);

#endif //HOMEWORK_MAXHEAP_H
