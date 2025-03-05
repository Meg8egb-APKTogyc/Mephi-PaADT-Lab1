#include "TypesOperator.h"


void *change_int_to_void(int a) {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = a;
    return ptr;
}

void *change_float_to_void(float a) {
    float *ptr = (float *)malloc(sizeof(float));
    *ptr = a;
    return ptr;
}

void *change_string_to_void(char* a) {
    char **ptr = (char **)malloc(sizeof(char *)); 
    *ptr = a;
    return ptr;
}

void assign_void_to_int(void *a, int *val) {
    *val = *(int *)a;
}

void assign_void_to_float(void *a, float *val) {
    *val = *(float *)a;
}

void assign_void_to_string(void *a, char **val) {
    *val = *(char **) a;
}

type_t int_to_type_t() {
    return INT;
}

type_t float_to_type_t() {
    return FLOAT;
}

type_t string_to_type_t() {
    return STRING;
}

int change_void_to_int(void *a) {
    int val = *(int *)a;
    return val;
}

float change_void_to_float(void *a) {
    float val = *(float *)a;
    return val;
}

char* change_void_to_string(void *a) {
    char *val = *(char **) a;
    return val;
}