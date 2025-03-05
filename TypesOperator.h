#pragma once
#include <stdlib.h>


typedef enum type {
    INT,
    FLOAT,
    STRING,
} type_t;


void *change_int_to_void(int a);

void *change_float_to_void(float a);

void *change_string_to_void(char *a);

#define change_to_void(X) _Generic((X),\
    int: change_int_to_void,\
    float: change_float_to_void,\
    char*: change_string_to_void\
) (X)


void assign_void_to_int(void *a, int *val);

void assign_void_to_float(void *a, float *val);

void assign_void_to_string(void *a, char **val);

#define assign_from_void(X, Y) _Generic((Y),\
    int*: assign_void_to_int,\
    float*: assign_void_to_float,\
    char**: assign_void_to_string\
) (X, Y)

type_t int_to_type_t();

type_t float_to_type_t();

type_t string_to_type_t();

#define change_to_type_t(X) _Generic((X), \
    int: int_to_type_t, \
    float: float_to_type_t, \
    char*: string_to_type_t \
)()

int change_void_to_int(void *a);

float change_void_to_float(void *a);

char* change_void_to_string(void *a);