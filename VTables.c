#include "Vtables.h"

static Types_vtable_t* int_vtable = NULL;
static Types_vtable_t* float_vtable = NULL;
static Types_vtable_t* string_vtable = NULL;


Types_vtable_t* get_int_vtable() {
    if (int_vtable == NULL) {
        int_vtable = (Types_vtable_t*) malloc(sizeof(Types_vtable_t));
        int_vtable -> dataAlloc = &dataAlloc_int;
        int_vtable -> toString = &toString_int;
        int_vtable -> compare = &compare_int;
    }

    return int_vtable;
}

Types_vtable_t* get_float_vtable() {
    if (float_vtable == NULL) {
        float_vtable = (Types_vtable_t*) malloc(sizeof(Types_vtable_t));
        float_vtable -> dataAlloc = &dataAlloc_float;
        float_vtable -> toString = &toString_float;
        float_vtable -> compare = &compare_float;
    }

    return float_vtable;
}


Types_vtable_t* get_string_vtable() {
    if (string_vtable == NULL) {
        string_vtable = (Types_vtable_t*) malloc(sizeof(Types_vtable_t));
        string_vtable -> dataAlloc = &dataAlloc_string;
        string_vtable -> toString = &toString_string;
        string_vtable -> compare = &compare_string;
    }

    return string_vtable;
}



void* dataAlloc_int(int count, int capacity, int elemSize) {
    int* new_array = malloc(capacity * elemSize);

    for (int i = 0; i < count; ++i) {
        new_array[i] = 0;
    }

    return new_array;
}


void* dataAlloc_float(int count, int capacity, int elemSize) {
    float* new_array = malloc(capacity * elemSize);

    for (int i = 0; i < count; ++i) {
        new_array[i] = 0;
    }

    return new_array;
}


void* dataAlloc_string(int count, int capacity, int elemSize) {
    char* new_array = malloc(capacity * elemSize);

    for (int i = 0; i < count; ++i) {
        char* str = (char*)new_array + i * elemSize;
        str[0] = '\0';
    }

    return new_array;
}


void* dataAlloc(Types_vtable_t* vtable, int count, int capacity, int elemSize) {
    return vtable -> dataAlloc(count, capacity, elemSize);
}

char* toString_int(void* a, int elemSize) {
    char* buff = (char*)malloc(12);

    sprintf(buff, "%i", *(int *)a);
    
    return buff; 
}

char* toString_float(void* a, int elSize) {
    char* buff = (char*)malloc(15);

    sprintf(buff, "%f", *(float *)a);
    
    return buff; 
}

char* toString_string(void* a, int elSize) {
    char* buff = (char *)malloc(elSize);

    sprintf(buff, "%s", (char*)a);

    return buff;
}

char* toString(Types_vtable_t* vtable, void* a, int elSize) {
    return vtable -> toString(a, elSize);
}


bool compare_int(void* a, void* b) {
    int val1 = *(int *)a;
    int val2 = *(int *)b;

    return val1 > val2;
}

bool compare_float(void* a, void* b) {
    float val1 = *(float *)a;
    float val2 = *(float *)b;

    return val1 > val2;
}

bool compare_string(void* a, void* b) {
    char* stra = (char *)a;
    int len1 = strlen(stra);

    char* strb = (char *)b;
    int len2 = strlen(strb);

    return len1 > len2;
}

bool compare(Types_vtable_t* vtable, void* a, void* b) {
    return vtable -> compare(a, b);
}