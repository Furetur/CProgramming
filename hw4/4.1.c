//
// Created by furetur on 03.03.2020.
//

#include "stdio.h"
#include "../lib/linkedlist/linkedlist.h"


int main()
{
    int soldiersNum = 0;
    // every [killStep]th soldier is killed
    int killStep = 0;

    printf("Enter the number of soldiers:\n");
    scanf("%d", &soldiersNum);

    printf("Every n-th soldier is killed. Enter n:\n");
    scanf("%d", &killStep);

    if (soldiersNum == 0) {
        printf("No soldiers - no deaths\n");
        return 0;
    }

    LinkedList* list = newLinkedList();

    for (int i = 0; i < soldiersNum; ++i) {
        linkedListPushBack(list, i + 1);
    }

    linkedListCreateLoop(list);

    LinkedListIterator* iterator = getLinkedListIterator(list);

    while(linkedListIteratorHasNext(iterator) && list->size > 1)
    {
        if ((iterator->traversedItems + 1) % killStep == 0)
        {
            linkedListIteratorDeleteNext(iterator);
        } else {
            linkedListIteratorGetNext(iterator);
        }
    }

    printf("The soldier who survives has the number %d in the initial list", list->head->val);


    deleteLinkedListIterator(iterator);
    deleteLinkedList(list);

    return 0;
}

