//
// Created by furet on 26.02.2020.
//
#include <stdbool.h>

#ifndef HOMEWORK_ARRAYUTILS_H
#define HOMEWORK_ARRAYUTILS_H


void emptyCharArray(char* array, int size);

char* createCharArray(int size);

int* createIntArray(int size);

int* createIntArrayWithVal(int size, int defaultVal);

bool* createBoolArray(int size);

bool* createBoolArrayWithVal(int size, bool val);

int** createInt2dArrayWithVal(int numRows, int numCols, int val);

int** createInt2dArray(int numRows, int numCols);

void readInt2dArray(int** arr, int numRows, int numCols);

bool** createBool2dArray(int numRows, int numCols);

bool** createBool2dArrayWithVal(int numRows, int numCols, bool val);

void freeInt2dArray(int** array, int numRows);

void freeBool2dArray(bool** array, int numRows);

void readIntArray(int arr[], int size);

void printIntArray(const int arr[], int size);

void emptyIntArray(int arr[], int size);

char* copyCharArray(char* array);

void writeCharArrayIntoArray(char* parentArray, char* childArray, int parentArrayStartIndex);

void reverseIntArray(int arr[], int start, int end);

bool areArraysEqual(const char* arr1, const char* arr2, int size);

char* getSubarray(const char* array, int start, int end);

int* copyIntArray(const int* array, int size);

void quickSort(int* arr,int startIndex,int endIndex);


#endif //HOMEWORK_ARRAYUTILS_H
