//
// Created by furetur on 04.03.2020.
//

#ifndef HOMEWORK_LINKEDLIST_H
#define HOMEWORK_LINKEDLIST_H


#include <stdbool.h>

typedef struct LinkedListItem
{
    struct LinkedListItem* prev;
    struct LinkedListItem* next;
    int val;
} LinkedListItem;


typedef struct LinkedList
{
    int size;
    LinkedListItem* head;
    LinkedListItem* tail;
} LinkedList;


typedef struct LinkedListIterator
{
    int traversedItems;
    LinkedList* list;
    LinkedListItem* curItem;
} LinkedListIterator;


LinkedListItem* newLinkedListItem(int val, LinkedListItem *next, LinkedListItem *prev);

void deleteLinkedListItem(LinkedListItem* linkedListItem);

LinkedList* newLinkedList();

LinkedListIterator* getLinkedListIterator(LinkedList* list);

bool linkedListIteratorHasNext(struct LinkedListIterator* iterator);

int linkedListIteratorGetNext(struct LinkedListIterator* iterator);

void deleteLinkedList(struct LinkedList* list);

LinkedListItem* linkedListGetItem(struct LinkedList* list, int index);

int linkedListGet(LinkedList* list, int index);

int linkedListDeleteItem(struct LinkedList* list, int index);

void linkedListInsertItem(LinkedList* list, int val, int index);

void linkedListPushBack(LinkedList* list, int val);

void linkedListPushFront(struct LinkedList* list, int val);

int linkedListPopBack(struct LinkedList* list);

int linkedListPopFront(struct LinkedList* list);

void linkedListCreateLoop(struct LinkedList* list);

int linkedListIteratorDeleteNext(LinkedListIterator* iterator);

#endif //HOMEWORK_LINKEDLIST_H
