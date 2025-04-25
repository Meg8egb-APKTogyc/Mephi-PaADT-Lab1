#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef void* (*dataAlloc_t) (int, int, int);
typedef char* (*toString_t) (void*, int);
typedef bool (*compare_t) (void*, void*);

typedef struct Types_vtable 
{
    dataAlloc_t dataAlloc;
    toString_t toString;
    compare_t compare;
} Types_vtable_t;


Types_vtable_t* get_int_vtable();
Types_vtable_t* get_float_vtable();
Types_vtable_t* get_string_vtable();


void* dataAlloc(Types_vtable_t* vtable, int count, int capacity, int elemSize);
void* dataAlloc_int(int count, int capacity, int elemSize);
void* dataAlloc_float(int count, int capacity, int elemSize);
void* dataAlloc_string(int count, int capacity, int elemSize);


char* toString(Types_vtable_t* vtable, void* val, int elSize);
char* toString_int(void* val, int elSize);
char* toString_float(void* val, int elSize);
char* toString_string(void* val, int elSize);


bool compare(Types_vtable_t* vtable, void* a, void* b);
bool compare_int(void* a, void* b);
bool compare_float(void* a, void* b);
bool compare_string(void* a, void* b);