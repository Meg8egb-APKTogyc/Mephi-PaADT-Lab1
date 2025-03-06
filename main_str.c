#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"


bool compare(void* a, void* b) {
    char* stra = (char *)a;
    int len1 = strlen(stra);

    char* strb = (char *)b;
    int len2 = strlen(strb);

    return len1 > len2;
}


void* addExclaimation(void* a) {
    char* str = (char*)a;
    int len = strlen(str);

    char* newStr = (char*)malloc((10) * sizeof(char));
    strcpy(newStr, str);

    newStr[len] = '!';
    newStr[len + 1] = '\0';

    return newStr;
}

bool isBigLength(void* a) {
    char* str = (char *)a;
    int len = strlen(str);
    return len > 3;
}


void* getMax(void* a, void* b) {
    char* stra = (char *)a;
    int len1 = strlen(stra);

    char* strb = (char *)b;
    int len2 = strlen(strb);

    char* newStr = (char*)malloc((10) * sizeof(char));
    if (len1 > len2) {
        strcpy(newStr, stra);
    } else {
        strcpy(newStr, strb);
    }
    return newStr;
}


void getInput(DynamicArray_t* da, int elsz) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char* type;
        scanf("%s", type);

        if (strcmp(type, "set") == 0) {
            int idx;
            char* val = (char *)malloc(elsz);
            scanf("%d %s", &idx, val);

            setVoidElement(da, (void *)val, idx);
        } else if (strcmp(type, "get") == 0) {
            int idx;
            scanf("%d", &idx);

            char* selem = (char *)getElementVoid(da, idx);
            puts(selem);
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
            DynamicArray_t* mapda = mapDynamicArray(da, addExclaimation);
            char* smapda = toString(mapda);
            puts(smapda);
            freeDynamicArray(mapda);
            free(smapda);
        } else if (strcmp(type, "where") == 0) {
            DynamicArray_t* wheda = whereDynamicArray(da, isBigLength);
            char* swheda = toString(wheda);
            puts(swheda);
            freeDynamicArray(wheda);
            free(swheda);
        } else if (strcmp(type, "reduce") == 0) {
            char* sredda = reduceDynamicArray(da, getMax);
            puts(sredda);
        }

        printf("%i. ", i + 1);
        char* sda = toString(da);
        puts(sda);
        printf("\n");
    }

    printf("\n");
}


int main() {
    int sz1, sz2, elsz;
    scanf("%d %d", &sz1, &sz2);
    scanf("%d %d", &elsz);

    DynamicArray_t* da1 = new_DynamicArray(get_string_DynamicArray_vtable(), sz1, elsz + 1);
    DynamicArray_t* da2 = new_DynamicArray(get_string_DynamicArray_vtable(), sz2, elsz + 1);

    getInput(da1, elsz);
    getInput(da2, elsz);

    DynamicArray_t* cda = concatenateDynamicArrays(da1, da2);
    char* scda = toString(cda);

    puts(scda);

    return EXIT_SUCCESS;
}
