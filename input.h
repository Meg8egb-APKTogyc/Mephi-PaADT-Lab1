#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "DynamicArray.h"

typedef enum {
    DATA_INT,
    DATA_FLOAT,
    DATA_STRING
} DataType;

bool compareFloat(void* a, void* b);

void* multiplyByTwoFloat(void* a);

bool isBigFloat(void* a);

void* getMinFloat(void* a, void* b);


bool compareInt(void* a, void* b);

void* multiplyByTwoInt(void* a);

bool isBigInt(void* a);

void* getMinInt(void* a, void* b);


bool compareStr(void* a, void* b);

void* multiplyByTwoStr(void* a);

bool isBigStr(void* a);

void* getMinStr(void* a, void* b);


void getInput(
    DynamicArray_t* da,
    int elsz,
    DataType dataType,
    VoidFunctionSort sortF,
    VoidFunctionMap mapF,
    VoidFunctionWhere whereF,
    VoidFunctionReduce reduceF,
    DA_ErrorCode* error
);


void getInputInt(DynamicArray_t* da, int elsz, DA_ErrorCode* error);

void getInputFloat(DynamicArray_t* da, int elsz, DA_ErrorCode* error);

void getInputStr(DynamicArray_t* da, int elsz, DA_ErrorCode* error);