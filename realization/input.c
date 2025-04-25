#include "../headers/input.h"


bool compareFloat(void* a, void* b) {
    float val1 = *(float *)a;
    float val2 = *(float *)b;

    return val1 > val2;
}


void* multiplyByTwoFloat(void* a) {
    float* val = malloc(sizeof(float));
    *val = *(float *)a;
    return val;
}

bool isBigFloat(void* a) {
    float val = *(float *)a;
    return val < 10;
}


void* getMinFloat(void* a, void* b) {
    float* val1 = malloc(sizeof(float));
    float* val2 = malloc(sizeof(float));
    *val1 = *(float *)a;
    *val2 = *(float *)a;

    return (val1 < val2) ? val1 : val2;
}


bool compareInt(void* a, void* b) {
    int val1 = *(int *)a;
    int val2 = *(int *)b;

    return val1 > val2;
}


void* multiplyByTwoInt(void* a) {
    int* val = malloc(sizeof(int));
    *val = *(int *)a;
    return val;
}

bool isBigInt(void* a) {
    int val = *(int *)a;
    return val < 10;
}


void* getMinInt(void* a, void* b) {
    int* val1 = malloc(sizeof(int));
    int* val2 = malloc(sizeof(int));
    *val1 = *(int *)a;
    *val2 = *(int *)a;

    return (val1 < val2) ? val1 : val2;
}


bool compareStr(void* a, void* b) {
    char* stra = (char *)a;
    int len1 = strlen(stra);

    char* strb = (char *)b;
    int len2 = strlen(strb);

    return len1 > len2;
}


void* addExclaimationStr(void* a) {
    char* str = (char*)a;
    int len = strlen(str);

    char* newStr = (char*)malloc((10) * sizeof(char));
    strcpy(newStr, str);

    newStr[len] = '!';
    newStr[len + 1] = '\0';

    return newStr;
}

bool isBigLengthStr(void* a) {
    char* str = (char *)a;
    int len = strlen(str);
    return len > 3;
}


void* getMaxStr(void* a, void* b) {
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

void getInputInt(DynamicArray_t* da, int elsz, DA_ErrorCode* error) {
    getInput(
        da, elsz, DATA_INT,
        compareInt, multiplyByTwoInt, isBigInt, getMinInt, error
    );
}

void getInputFloat(DynamicArray_t* da, int elsz, DA_ErrorCode* error) {
    getInput(
        da, elsz, DATA_FLOAT,
        compareFloat, multiplyByTwoFloat, isBigFloat, getMinFloat, error
    );
}

void getInputStr(DynamicArray_t* da, int elsz, DA_ErrorCode* error) {
    getInput(
        da, elsz, DATA_STRING,
        compareStr, addExclaimationStr, isBigLengthStr, getMaxStr, error
    );
}




void getInput(
    DynamicArray_t* da,
    int elsz,
    DataType dataType,
    VoidFunctionSort sortF,
    VoidFunctionMap mapF,
    VoidFunctionWhere whereF,
    VoidFunctionReduce reduceF,
    DA_ErrorCode* error
) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char* type = malloc(10);
        scanf("%s", type);

        if (strcmp(type, "set") == 0) {
            int idx;
            scanf("%i", &idx);

            void* val = malloc(elsz);
            
            switch (dataType)
            {
            case DATA_INT:
                scanf("%i", (int *)val);
                break;
            case DATA_FLOAT:
                scanf("%f", (float*)val);
                break;
            case DATA_STRING:
                scanf("%s", (char*)val);
                break;
            }

            setVoidElementEr(da, (void *)val, idx, error);
            CHECK_ERROR(*error);
        } else if (strcmp(type, "get") == 0) {
            int idx;
            scanf("%d", &idx);

            char* selem = (char *)toString(da -> funcs, getElementVoidEr(da, idx, error), da -> data -> elementSize);
            CHECK_ERROR(*error);
            puts(selem);
        } else if (strcmp(type, "res") == 0) {
            int sz;
            scanf("%d", &sz);

            resizeEr(da, sz, error);
        } else if (strcmp(type, "sort") == 0) {
            DynamicArray_t* soda = mergeSortEr(da, NULL, error);
            char* ssoda = DAtoStringEr(soda, error);
            puts(ssoda);
            freeDynamicArrayEr(soda, error);
            free(ssoda);
        } else if (strcmp(type, "map") == 0) {
            DynamicArray_t* mapda = mapDynamicArrayEr(da, mapF, error);
            char* smapda = DAtoStringEr(mapda, error);
            puts(smapda);
            freeDynamicArrayEr(mapda, error);
            free(smapda);
        } else if (strcmp(type, "where") == 0) {
            DynamicArray_t* wheda = whereDynamicArrayEr(da, whereF, error);
            char* swheda = DAtoStringEr(wheda, error);
            puts(swheda);
            freeDynamicArrayEr(wheda, error);
            free(swheda);
        } else if (strcmp(type, "reduce") == 0) {
            char* sredda = toString(da -> funcs, reduceDynamicArrayEr(da, reduceF, error), da -> data -> elementSize);
            puts(sredda);
        }

        printf("%i. ", i + 1);
        char* sda = DAtoStringEr(da, error);
        puts(sda);
        printf("\n");
    }

    printf("\n");
}