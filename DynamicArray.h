#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct DynamicArray;


typedef struct DynamicArray_data
{
    int count;
    int capacity;
    int elementSize;
    void* array;
} DynamicArray_data_t;


typedef void (*dataAlloc_t) (struct DynamicArray_data*, int, int);
typedef char* (*toString_t) (struct DynamicArray*);
typedef bool (*compare_t) (struct DynamicArray*, int, struct DynamicArray*, int);

typedef struct DynamicArray_vtable 
{
    dataAlloc_t dataAlloc;
    toString_t toString;
    compare_t compare;
} DynamicArray_vtable_t;


typedef struct DynamicArray {
    DynamicArray_data_t* data;
    DynamicArray_vtable_t* funcs;
} DynamicArray_t;


typedef bool (*VoidFunctionSort)(void *, void *);
typedef void* (*VoidFunctionMap)(void *);
typedef bool (*VoidFunctionWhere)(void *);
typedef void* (*VoidFunctionReduce)(void *, void *);


DynamicArray_t* new_DynamicArray(DynamicArray_vtable_t* funcs, int size, int elemSize);

#define newDynamicArray(X, Y) new_DynamicArray(X, Y, 0)


void DynamicArray_data_alloc(DynamicArray_t* da, int sz, int elemSize);
void DynamicArray_data_alloc_int(DynamicArray_data_t* da_data, int sz, int elemSize);
void DynamicArray_data_alloc_float(DynamicArray_data_t* da_data, int sz, int elemSize);
void DynamicArray_data_alloc_string(DynamicArray_data_t* da_data, int sz, int elemSize);

void freeDynamicArray(DynamicArray_t* da);

void resize(DynamicArray_t* da, int sz);

char* toString(DynamicArray_t* da);
char* toStringInt(DynamicArray_t* da);
char* toStringFloat(DynamicArray_t* da);
char* toStringString(DynamicArray_t* da);


DynamicArray_vtable_t* get_int_DynamicArray_vtable();
DynamicArray_vtable_t* get_float_DynamicArray_vtable();
DynamicArray_vtable_t* get_string_DynamicArray_vtable();


void* getElementVoid(DynamicArray_t* da, int idx);

void setVoidElement(DynamicArray_t* da, void* val, int idx);

void pushBackVoid(DynamicArray_t* da, void* val);

void popBack(DynamicArray_t* da);

int getLenght(DynamicArray_t* da);


DynamicArray_t* concatenateDynamicArrays(DynamicArray_t* da1, DynamicArray_t* da2);

DynamicArray_t* merge(DynamicArray_t* da1, DynamicArray_t* da2, VoidFunctionSort func);

DynamicArray_t* mergeSort(DynamicArray_t* da, VoidFunctionSort func);

DynamicArray_t* mapDynamicArray(DynamicArray_t* da, VoidFunctionMap func);

DynamicArray_t* whereDynamicArray(DynamicArray_t* da, VoidFunctionWhere func);

void* reduceDynamicArray(DynamicArray_t* da, VoidFunctionReduce func);