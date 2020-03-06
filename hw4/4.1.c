//
// Created by furetur on 03.03.2020.
//

#include <stddef.h>
#include <stdlib.h>
#include "stdio.h"
#include "../lib/linkedlist/linkedlist.h"


int main()
{
//    int soldiersNum = 0;
//    // every [killStep]th soldier is killed
//    int killStep = 0;
//
//    printf("Enter the number of soldiers:\n");
//    scanf("%d", &soldiersNum);
//
//    printf("Every n-th soldier is killed. Enter n:\n");
//    scanf("%d", &killStep);
//
//    LinkedList* list = newLinkedList();
//
//    for (int i = 0; i < soldiersNum; ++i) {
//        linkedListPushBack(list, i + 1);
//    }
//
//    linkedListCreateLoop(list);
//
//    LinkedListIterator* iterator = getLinkedListIterator(list);
//
//    while(linkedListIteratorHasNext(iterator) && list->size > 1)
//    {
//        if ((iterator->traversedItems + 1) % killStep == 0)
//        {
//            linkedListIteratorDeleteNext(iterator);
//        } else {
//            linkedListIteratorGetNext(iterator);
//        }
//    }
//
//    LinkedListIterator* it = getLinkedListIterator(list);
//
//    while(linkedListIteratorHasNext(it) && it->traversedItems < 10)
//    {
//        printf("cur: %d\n", linkedListIteratorGetNext(it));
//    }

    LinkedList* list = newLinkedList();

    for (int i = 0; i < 10; ++i) {
        linkedListPushBack(list, i);
    }

    for (int i = 0; i < 5; ++i) {
        linkedListPopBack(list);
    }

    LinkedListIterator* iterator = getLinkedListIterator(list);

    while (linkedListIteratorHasNext(iterator) && iterator->traversedItems < 10)
    {
        printf("Cur %d\n", linkedListIteratorGetNext(iterator));
    }

    free(iterator);
    deleteLinkedList(list);

    return 0;
}

