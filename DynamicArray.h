#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TypesOperator.c"


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
typedef type_t (*getType_t) ();


typedef struct DynamicArray_vtable 
{
    dataAlloc_t dataAlloc;
    toString_t toString;
    compare_t compare;
    getType_t getType;
} DynamicArray_vtable_t;


typedef struct DynamicArray {
    DynamicArray_data_t* data;
    DynamicArray_vtable_t* funcs;
} DynamicArray_t;


typedef int (*MapFunctionInt_t)(int);
typedef float (*MapFunctionFloat_t)(float);
typedef char* (*MapFunctionString_t)(char*);


typedef union {
    MapFunctionInt_t MapFunctionInt;
    MapFunctionFloat_t MapFunctionFloat;
    MapFunctionString_t MapFunctionString;
} MapFunctionUnion_t;



typedef bool (*WhereFunctionInt_t)(int);
typedef bool (*WhereFunctionFloat_t)(float);
typedef bool (*WhereFunctionString_t)(char*);


typedef union {
    WhereFunctionInt_t WhereFunctionInt;
    WhereFunctionFloat_t WhereFunctionFloat;
} WhereFunctionUnion_t;


typedef int (*ReduceFunctionInt_t)(int, int);
typedef float (*ReduceFunctionFloat_t)(float, float);


typedef union {
    ReduceFunctionInt_t ReduceFunctionInt;
    ReduceFunctionFloat_t ReduceFunctionFloat;
} ReduceFunctionUnion_t;


DynamicArray_t* new_DynamicArray(DynamicArray_vtable_t* funcs, int size, int elemSize);

#define newDynamicArray(X, Y) new_DynamicArray(X, Y, 0)

type_t getType(DynamicArray_t* da);
type_t getTypeInt();
type_t getTypeFloat();
type_t getTypeString();


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


bool compare(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2);
bool compareInt(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2);
bool compareFloat(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2);
bool compareString(DynamicArray_t* da, int idx1, DynamicArray_t* da2, int idx2);


DynamicArray_vtable_t* get_int_DynamicArray_vtable();
DynamicArray_vtable_t* get_float_DynamicArray_vtable();


void* getElementVoid(DynamicArray_t* da, int idx);

void setVoidElement(DynamicArray_t* da, void* val, int idx);

void pushBackVoid(DynamicArray_t* da, void* val);


#define pushBack(X, Y) pushBackVoid(X, change_to_void(Y))


int getLenght(DynamicArray_t* da);


DynamicArray_t* concatenationDynamicArrays(DynamicArray_t* da1, DynamicArray_t* da2);

DynamicArray_t* merge(DynamicArray_t* da1, DynamicArray_t* da2);

DynamicArray_t* mergeSort(DynamicArray_t* da);

DynamicArray_t* mapDynamicArray(DynamicArray_t* da, MapFunctionUnion_t* func);

DynamicArray_t* whereDynamicArray(DynamicArray_t* da, WhereFunctionUnion_t* func);

void* reduceDynamicArray(DynamicArray_t* da, ReduceFunctionUnion_t* func);