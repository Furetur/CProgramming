//
// Created by furetur on 04.03.2020.
//

#include "linkedlist.h"
#include "stdlib.h"


LinkedList* newLinkedList()
{
    LinkedList* list = malloc(sizeof(LinkedList));
    list->size = 0;
    list->tail = NULL;
    list->head = NULL;
    return list;
}


LinkedListItem* newLinkedListItem(const int val, LinkedListItem *next, LinkedListItem *prev)
{
    LinkedListItem* item = malloc(sizeof(LinkedListItem));
    item->val = val;
    item->prev = prev;
    item->next = next;
    return item;
}


void deleteLinkedListItem(LinkedListItem* linkedListItem)
{
    free(linkedListItem);
}


LinkedListIterator* getLinkedListIterator(LinkedList* list)
{
    LinkedListIterator* iterator = malloc(sizeof(LinkedListIterator));
    LinkedListItem* nullItem = newLinkedListItem(0, list->head, NULL);

    iterator->curItem = nullItem;
    iterator->traversedItems = 0;
    iterator->atNullItem = true;
    iterator->list = list;

    return iterator;
}


void deleteLinkedListIterator(LinkedListIterator* iterator)
{
    if (iterator->atNullItem)
    {
        deleteLinkedListItem(iterator->curItem);
    }
    free(iterator);
}


bool linkedListIteratorHasNext(struct LinkedListIterator* iterator)
{
    return iterator->curItem->next != NULL;
}


int linkedListIteratorGetNext(struct LinkedListIterator* iterator)
{
    if (!linkedListIteratorHasNext(iterator))
    {
        return -1;
    }

    LinkedListItem* prevItem = iterator->curItem;
    iterator->curItem = iterator->curItem->next;

    if (iterator->atNullItem)
    {
        deleteLinkedListItem(prevItem);
    }

    iterator->traversedItems++;
    iterator->atNullItem = false;
    return iterator->curItem->val;
}


void linkedListItemPullOut(struct LinkedList* list, LinkedListItem* item)
{
    if (item == NULL)
    {
        return;
    }

    LinkedListItem* prevItem = item->prev;
    LinkedListItem* nextItem = item->next;


    if (prevItem != NULL)
    {
        if (prevItem->next != item)
        {
            // corrupt item
            return;
        }
        prevItem->next = nextItem;
    }

    if (nextItem != NULL)
    {
        if (nextItem->prev != item)
        {
            // corrupt item
            return;
        }
        nextItem->prev = prevItem;
    }

    if (list->head == item && item == list->tail)
    {
        // one element loop
        list->head = NULL;
        list->tail = NULL;
    }

    if (list->head == item)
    {
        list->head = item->next;
    }
    if (list->tail == item)
    {
        list->tail = item->prev;
    }


    list->size--;

    item->prev = NULL;
    item->next = NULL;

    deleteLinkedListItem(item);
}

// does not move the iterator forward
int linkedListIteratorDeleteNext(LinkedListIterator* iterator)
{
    if (!linkedListIteratorHasNext(iterator))
    {
        return -1;
    }

    LinkedListItem* nextItem = iterator->curItem->next;

    const int nextItemVal = nextItem->val;

    if (iterator->atNullItem)
    {
        // because the starting iterator's node is a fake node
        iterator->curItem->next = nextItem->next;
    }

    linkedListItemPullOut(iterator->list, nextItem);

    iterator->traversedItems++;

    return nextItemVal;
}


void deleteLinkedList(struct LinkedList* list)
{
    const int listInitialSize = list->size;

    if (listInitialSize == 0)
    {
        free(list);
        return;
    }

    // remove loops
    list->tail->next = NULL;
    list->head->prev = NULL;

    LinkedListIterator* iterator = getLinkedListIterator(list);
    while (linkedListIteratorHasNext(iterator) && iterator->traversedItems < listInitialSize)
    {
        linkedListIteratorGetNext(iterator);
        if (iterator->curItem->prev == NULL)
        {
            continue;
        }
        LinkedListItem* prevItem = iterator->curItem->prev;
        iterator->curItem->prev = NULL;
        deleteLinkedListItem(prevItem);
    }
    if (iterator->curItem != NULL)
    {
        deleteLinkedListItem(iterator->curItem);
    }
    deleteLinkedListIterator(iterator);
    free(list);
}


LinkedListItem* linkedListGetItem(struct LinkedList* list, const int index)
{
    LinkedListIterator* iterator = getLinkedListIterator(list);

    while (linkedListIteratorHasNext(iterator) && iterator->traversedItems < index + 1)
    {
        linkedListIteratorGetNext(iterator);
    }

    if (index + 1 != iterator->traversedItems)
    {
        deleteLinkedListIterator(iterator);
        return NULL;
    }

    LinkedListItem* result = iterator->curItem;

    deleteLinkedListIterator(iterator);

    return result;
}


int linkedListGet(LinkedList* list, const int index)
{
    LinkedListItem* item = linkedListGetItem(list, index);
    if (item == NULL)
    {
        return -1;
    }
    return item->val;
}


int linkedListDeleteItem(struct LinkedList* list, const int index)
{
    if (list->size == 0)
    {
        return -1;
    }
    LinkedListItem* curItem = linkedListGetItem(list, index);

    if (curItem == NULL)
    {
        return -1;
    }

    int curItemVal = curItem->val;

    linkedListItemPullOut(list, curItem);

    return curItemVal;
}


void linkedListInsertItem(LinkedList* list, const int val, const int index)
{
    if (list->size == 0)
    {
        struct LinkedListItem* newItem = newLinkedListItem(val, NULL, NULL);
        list->head = newItem;
        list->tail = newItem;
        list->size++;
        return;
    }

    if (index == list->size)
    {
        // list->tail->next because the list might be cyclic
        struct LinkedListItem* newItem = newLinkedListItem(val, list->tail->next, list->tail);
        list->tail->next = newItem;
        list->tail = newItem;
        list->size++;
        return;
    }

    struct LinkedListItem* itemAtIndex = linkedListGetItem(list, index);

    if (itemAtIndex == NULL)
    {
        // out of bound
        return;
    }

    LinkedListItem* prevItem = itemAtIndex->prev;

    struct LinkedListItem* newItem = newLinkedListItem(val, itemAtIndex, prevItem);

    if (prevItem != NULL)
    {
        prevItem->next = newItem;
    }

    itemAtIndex->prev = newItem;
    list->size++;
}


void linkedListPushBack(LinkedList* list, const int val)
{
    linkedListInsertItem(list, val, list->size);
}


// optimized
void linkedListPushFront(struct LinkedList* list, const int val)
{
    linkedListInsertItem(list, val, 0);
}


// optimized
int linkedListPopBack(struct LinkedList* list)
{
    if (list->tail == NULL)
    {
        return -1;
    }

    const int tailValue = list->tail->val;
    linkedListItemPullOut(list, list->tail);

    return tailValue;
}


int linkedListPopFront(struct LinkedList* list)
{
    return linkedListDeleteItem(list, 0);
}


void linkedListCreateLoop(struct LinkedList* list)
{
    if (list->size == 0)
    {
        return;
    }

    list->head->prev = list->tail;
    list->tail->next = list->head;
}


bool linkedListContains(struct LinkedList* list, const int value)
{
    LinkedListIterator* iterator = getLinkedListIterator(list);

    while(linkedListIteratorHasNext(iterator))
    {
        const int curValue = linkedListIteratorGetNext(iterator);
        if (curValue == value)
        {
            deleteLinkedListIterator(iterator);
            return true;
        }
    }
    deleteLinkedListIterator(iterator);
    return false;
}
