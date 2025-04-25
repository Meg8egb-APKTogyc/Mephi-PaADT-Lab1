#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "VTables.h"
#include "ErrorHandler.h"


typedef ErrorCode DA_ErrorCode;

struct DynamicArray;


typedef struct DynamicArray_data
{
    int count;
    int capacity;
    int elementSize;
    void* array;
} DynamicArray_data_t;


typedef struct DynamicArray {
    DynamicArray_data_t* data;
    Types_vtable_t* funcs;
} DynamicArray_t;


typedef bool (*VoidFunctionSort)(void *, void *);
typedef void* (*VoidFunctionMap)(void *);
typedef bool (*VoidFunctionWhere)(void *);
typedef void* (*VoidFunctionReduce)(void *, void *);


DynamicArray_t* new_DynamicArrayEr(Types_vtable_t* funcs, int size, int elemSize, DA_ErrorCode* error);

#define newDynamicArray(X, Y) new_DynamicArrayEr(X, Y, 0, NULL)

ErrorCode* freeDynamicArrayEr(DynamicArray_t* da, DA_ErrorCode* error);

ErrorCode* resizeEr(DynamicArray_t* da, int sz, DA_ErrorCode* error);

char* DAtoStringEr(DynamicArray_t* da, DA_ErrorCode* error);

int _getCapacity(int sz);

void* getElementVoidEr(DynamicArray_t* da, int idx, DA_ErrorCode* error);

ErrorCode* setVoidElementEr(DynamicArray_t* da, void* val, int idx, DA_ErrorCode* error);

ErrorCode* pushBackVoidEr(DynamicArray_t* da, void* val, DA_ErrorCode* error);

ErrorCode* popBackEr(DynamicArray_t* da, DA_ErrorCode* error);

int getLenghtEr(DynamicArray_t* da, DA_ErrorCode* error);


DynamicArray_t* concatenateDynamicArraysEr(DynamicArray_t* da1, DynamicArray_t* da2, DA_ErrorCode* error);

DynamicArray_t* mergeEr(DynamicArray_t* da1, DynamicArray_t* da2, VoidFunctionSort func, DA_ErrorCode* error);

DynamicArray_t* mergeSortEr(DynamicArray_t* da, VoidFunctionSort func, DA_ErrorCode* error);

DynamicArray_t* mapDynamicArrayEr(DynamicArray_t* da, VoidFunctionMap func, DA_ErrorCode* error);

DynamicArray_t* whereDynamicArrayEr(DynamicArray_t* da, VoidFunctionWhere func, DA_ErrorCode* error);

void* reduceDynamicArrayEr(DynamicArray_t* da, VoidFunctionReduce func, DA_ErrorCode* error);