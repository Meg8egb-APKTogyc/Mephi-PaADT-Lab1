#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "DynamicArray.h"
#include "input.h"


int main() {
    int type;
    int sz1, sz2;
    scanf("%d", &type);
    scanf("%d %d", &sz1, &sz2);

    DA_ErrorCode err;

    if (type == 0) {
        int elsz;
        scanf("%d", &elsz);

        DynamicArray_t* da1 = new_DynamicArrayEr(get_string_vtable(), sz1, elsz + 1, &err);
        DynamicArray_t* da2 = new_DynamicArrayEr(get_string_vtable(), sz2, elsz + 1, &err);

        getInputStr(da1, elsz, &err);
        getInputStr(da2, elsz, &err);

        DynamicArray_t* cda = concatenateDynamicArraysEr(da1, da2, &err);
        char* scda = DAtoStringEr(cda, &err);

        puts(scda);

        freeDynamicArrayEr(da1, &err);
        freeDynamicArrayEr(da2, &err);
        freeDynamicArrayEr(cda, &err);
    } else if (type == 1) {
        int elsz = sizeof(int);
        DynamicArray_t* da1 = new_DynamicArrayEr(get_int_vtable(), sz1, elsz + 1, NULL);
        DynamicArray_t* da2 = new_DynamicArrayEr(get_int_vtable(), sz2, elsz + 1, NULL);

        getInputInt(da1, elsz, &err);
        getInputInt(da2, elsz, &err);

        DynamicArray_t* cda = concatenateDynamicArraysEr(da1, da2, &err);
        char* scda = DAtoStringEr(cda, &err);

        puts(scda);

        freeDynamicArrayEr(da1, &err);
        freeDynamicArrayEr(da2, &err);
        freeDynamicArrayEr(cda, &err);
    } else {
        int elsz = sizeof(float);
        DynamicArray_t* da1 = new_DynamicArrayEr(get_float_vtable(), sz1, elsz + 1, &err);
        DynamicArray_t* da2 = new_DynamicArrayEr(get_float_vtable(), sz2, elsz + 1, &err);

        getInputFloat(da1, elsz, &err);
        getInputFloat(da2, elsz, &err);

        DynamicArray_t* cda = concatenateDynamicArraysEr(da1, da2, &err);
        char* scda = DAtoStringEr(cda, &err);

        puts(scda);

        freeDynamicArrayEr(da1, &err);
        freeDynamicArrayEr(da2, &err);
        freeDynamicArrayEr(cda, &err);
    }



    return EXIT_SUCCESS;
}