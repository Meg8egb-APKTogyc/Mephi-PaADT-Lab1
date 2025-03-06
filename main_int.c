#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"


bool compare(void* a, void* b) {
    int val1 = *(int *)a;
    int val2 = *(int *)b;

    return val1 > val2;
}


void* multiplyByTwo(void* a) {
    int* val = malloc(sizeof(int));
    *val = *(int *)a;
    return val;
}

bool isBig(void* a) {
    int val = *(int *)a;
    return val < 10;
}


void* getMin(void* a, void* b) {
    int* val1 = malloc(sizeof(int));
    int* val2 = malloc(sizeof(int));
    *val1 = *(int *)a;
    *val2 = *(int *)a;

    return (val1 < val2) ? val1 : val2;
}


void getInput(DynamicArray_t* da, int elsz) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char* type = malloc(10);
        scanf("%s", type);

        if (strcmp(type, "set") == 0) {
            int idx;
            int val;
            scanf("%d %d", &idx, &val);

            setVoidElement(da, (void *)&val, idx);
        } else if (strcmp(type, "get") == 0) {
            int idx;
            scanf("%d", &idx);

            int* selem = (int *)getElementVoid(da, idx);
            printf("%i\n", *selem);
        } else if (strcmp(type, "res") == 0) {
            int sz;
            scanf("%d", &sz);

            resize(da, sz);
        } else if (strcmp(type, "sort") == 0) {
            DynamicArray_t* soda = mergeSort(da, compare);
            char* ssoda = toString(soda);
            puts(ssoda);
            freeDynamicArray(soda);
            free(ssoda);
        } else if (strcmp(type, "map") == 0) {
            DynamicArray_t* mapda = mapDynamicArray(da, multiplyByTwo);
            char* smapda = toString(mapda);
            puts(smapda);
            freeDynamicArray(mapda);
            free(smapda);
        } else if (strcmp(type, "where") == 0) {
            DynamicArray_t* wheda = whereDynamicArray(da, isBig);
            char* swheda = toString(wheda);
            puts(swheda);
            freeDynamicArray(wheda);
            free(swheda);
        } else if (strcmp(type, "reduce") == 0) {
            int* sredda = reduceDynamicArray(da, getMin);
            printf("%i\n", *sredda);
        }

        printf("%i. ", i + 1);
        char* sda = toString(da);
        puts(sda);
        printf("\n");
    }

    printf("\n");
}


int main() {
    int sz1, sz2;
    scanf("%d %d", &sz1, &sz2);

    DynamicArray_t* da1 = newDynamicArray(get_int_DynamicArray_vtable(), sz1);
    DynamicArray_t* da2 = newDynamicArray(get_int_DynamicArray_vtable(), sz2);

    getInput(da1, sizeof(int));
    getInput(da2, sizeof(int));

    DynamicArray_t* cda = concatenateDynamicArrays(da1, da2);
    char* scda = toString(cda);

    puts(scda);

    return EXIT_SUCCESS;
}
