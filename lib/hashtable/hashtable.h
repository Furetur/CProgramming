//
// Created by furetur on 01.03.2020.
//

#ifndef HOMEWORK_HASHTABLE_H
#define HOMEWORK_HASHTABLE_H




typedef struct DataItem
{
    char* key;
    char* val;
} DataItem;


typedef struct HashTable
{
    int size;
    int itemsCount;
    DataItem** items;

} HashTable;


const DataItem DELETED_DATA_ITEM;


void deleteHashTable(HashTable* hashTable);

HashTable* newHashTableSized(int desiredSize);

HashTable* newHashTable();

void hashTableInsert(HashTable* hashTable, char* key, char* value);

void hashTableDelete(HashTable* hashTable, char* key);

char* hashTableGet(HashTable* hashTable, char* key);



#endif //HOMEWORK_HASHTABLE_H
