//
// Created by furetur on 01.03.2020.
//

#include <string.h>
#include <stdbool.h>
#include "stdio.h"
#include <stdlib.h>
#include "../numberutils/numberutils.h"
#include "../stringutils/stringutils.h"
#include "../commonutils/commonutils.h"
#include "../arrayutils/arrayutils.h"
#include "hashtable.h"


const int HASHTABLE_DEFAULT_SIZE = 53;
const int HASHTABLE_PRIME1 = 131;
const int HASHTABLE_PRIME2 = 137;


const DataItem DELETED_DATA_ITEM = {NULL, NULL};


DataItem* newDataItem(char* key, char* value)
{
    DataItem* dataItem = malloc(sizeof(DataItem));
    dataItem->key = strdup(key);
    dataItem->val = strdup(value);
    return dataItem;
}

void deleteDataItem(DataItem* item)
{
    if (item->key == NULL && item->val == NULL)
    {
        return;
    }
    free(item->key);
    free(item->val);
    free(item);
}


void deleteHashTable(HashTable* hashTable)
{
    for (int i = 0; i < hashTable->size; ++i)
    {
        if (hashTable->items[i] == NULL)
        {
            continue;
        }
        deleteDataItem(hashTable->items[i]);
    }
    free(hashTable->items);
    free(hashTable);
}


HashTable* newHashTableSized(const int desiredSize)
{
    const int nextPrimeSize = nextPrime(desiredSize);
    HashTable* hashTable = malloc(sizeof(HashTable));

    hashTable->size = nextPrimeSize;
    hashTable->itemsCount = 0;
    hashTable->items = calloc(nextPrimeSize, sizeof(DataItem*));

    return hashTable;
}


HashTable* newHashTable()
{
    return newHashTableSized(HASHTABLE_DEFAULT_SIZE);
}


long long doubleHash(char* string, int modulo, int attempt)
{
    const long long hash1 = hashCode(string, HASHTABLE_PRIME1, modulo);
    const long long hash2 = hashCode(string, HASHTABLE_PRIME2, modulo);

    return (hash1 + attempt * (hash2 + 1)) % modulo;
}


void resizeHashTable(HashTable* hashTable, const int newSize)
{
    if (newSize < HASHTABLE_DEFAULT_SIZE)
    {
        return;
    }

    HashTable* newHashTable = newHashTableSized(newSize);

    for (int i = 0; i < hashTable->size; ++i)
    {
        const DataItem* curItem = hashTable->items[i];
        if (curItem == NULL || curItem == &DELETED_DATA_ITEM)
        {
            continue;
        }
        hashTableInsert(newHashTable, curItem->key, curItem->val);
    }

    swapInts(&hashTable->size, &newHashTable->size);
    swapInts(&hashTable->itemsCount, &newHashTable->itemsCount);

    DataItem** tempItems = hashTable->items;
    hashTable->items = newHashTable->items;
    newHashTable->items = tempItems;

    deleteHashTable(newHashTable);
}


void resizeHashTableUp(HashTable* hashTable)
{
    resizeHashTable(hashTable, 2 * hashTable->size);
}


void resizeHashTableDown(HashTable* hashTable)
{
    resizeHashTable(hashTable, hashTable->size / 2);
}


bool isHashTableOverloaded(HashTable* hashTable)
{
    return (hashTable->itemsCount * 100) / hashTable->size > 70;
}


bool isHashTableUnderloaded(HashTable* hashTable)
{
    return (hashTable->itemsCount * 100) / hashTable->size < 10;
}


void hashTableInsert(HashTable* hashTable, char* key, char* value)
{
    if (isHashTableOverloaded(hashTable))
    {
        resizeHashTableUp(hashTable);
    }

    int attempt = 0;
    long long hash = doubleHash(key, hashTable->size, attempt);
    DataItem* curItem = hashTable->items[hash];

    while (curItem != NULL && curItem != &DELETED_DATA_ITEM)
    {
        if (strcmp(curItem->key, key) == 0)
        {
            hashTable->items[hash] = NULL;
            deleteDataItem(curItem);
            break;
        }
        attempt++;
        hash = doubleHash(key, hashTable->size, attempt);
        curItem = hashTable->items[hash];
    }

    DataItem* dataItem = newDataItem(key, value);


    hashTable->items[hash] = dataItem;
    hashTable->itemsCount++;
}


void hashTableDelete(HashTable* hashTable, char* key)
{
    if (isHashTableUnderloaded(hashTable))
    {
        resizeHashTableDown(hashTable);
    }

    int attempt = 0;
    long long hash = doubleHash(key, hashTable->size, attempt);
    DataItem* curItem = hashTable->items[hash];

    while (curItem != NULL)
    {
        if (curItem != &DELETED_DATA_ITEM && strcmp(curItem->key, key) == 0)
        {
            deleteDataItem(curItem);
            hashTable->items[hash] = &DELETED_DATA_ITEM;
            return;
        }
        attempt++;
        hash = doubleHash(key, hashTable->size, attempt);
        curItem = hashTable->items[hash];
    }
    hashTable->itemsCount--;
}


char* hashTableGet(HashTable* hashTable, char* key)
{
    int attempt = 0;
    long long hash = doubleHash(key, hashTable->size, attempt);
    DataItem* curItem = hashTable->items[hash];

    while (curItem != NULL)
    {
        if (curItem != &DELETED_DATA_ITEM && strcmp(curItem->key, key) == 0)
        {
            return curItem->val;
        }
        attempt++;
        hash = doubleHash(key, hashTable->size, attempt);
        curItem = hashTable->items[hash];
    }
    return NULL;
}


