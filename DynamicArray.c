#include "DynamicArray.h"


static DynamicArray_vtable_t* int_vtable = NULL;
static DynamicArray_vtable_t* float_vtable = NULL;
static DynamicArray_vtable_t* string_vtable = NULL;


DynamicArray_t* new_DynamicArray(DynamicArray_vtable_t* funcs, int size, int elemSize) {
    DynamicArray_t* da = (DynamicArray_t*) malloc(sizeof(DynamicArray_t));
    da -> data = (DynamicArray_data_t*) malloc(sizeof(DynamicArray_data_t));

    da -> funcs = funcs;
    da -> funcs -> dataAlloc(da -> data, size, elemSize);

    return da;
}


int getCapacity(int size) {
    int bit = 1;
    while (bit <= size)
        bit = (bit << 1);

    return bit;
}


void DynamicArray_data_alloc(DynamicArray_t* da, int size, int elementSize) {
    if (da == NULL) exit(1);

    da -> funcs -> dataAlloc(da -> data, size, elementSize);
}

void DynamicArray_data_alloc_int(DynamicArray_data_t* da_data, int size, int elemSize) {
    da_data -> count = size;
    da_data -> capacity = getCapacity(size);
    da_data -> elementSize = sizeof(int);

    int* new_array = malloc(da_data -> capacity * da_data -> elementSize);
    
    for (int i = 0; i < da_data -> count; ++i) {
        new_array[i] = 0;
    }

    da_data -> array = new_array;
}

void DynamicArray_data_alloc_float(DynamicArray_data_t* da_data, int size, int elemSize) {
    da_data -> count = size;
    da_data -> capacity = getCapacity(size);
    da_data -> elementSize = sizeof(float);

    float* new_array = malloc(da_data -> capacity * da_data -> elementSize);
    
    for (int i = 0; i < da_data -> count; ++i) {
        new_array[i] = 0;
    }

    da_data -> array = new_array;
}


void DynamicArray_data_alloc_string(DynamicArray_data_t* da_data, int size, int elementSize) {
    da_data->count = size;
    da_data->capacity = getCapacity(size);
    da_data->elementSize = elementSize;

    da_data->array = malloc(da_data->capacity * da_data->elementSize);

    for (int i = 0; i < da_data->count; ++i) {
        char* str = (char*)da_data->array + i * da_data->elementSize;
        str[0] = '\0';
    }
}


type_t getType(DynamicArray_t* da) {
    return da -> funcs -> getType();
}


type_t getTypeInt() {
    return INT;
}


type_t getTypeFloat() {
    return FLOAT;
}

type_t getTypeString() {
    return STRING;
}


void freeDynamicArray(DynamicArray_t* da) {
    if (da == NULL) {
        return;
    }

    if (da->data != NULL) {
        if (da->data->array != NULL) {
            free(da->data->array);
            da->data->array = NULL;
        }
        free(da->data);
        da->data = NULL;
    }

    free(da);
}


DynamicArray_vtable_t* get_int_DynamicArray_vtable() {
    if (int_vtable == NULL) {
        int_vtable = (DynamicArray_vtable_t*) malloc(sizeof(DynamicArray_vtable_t));
        int_vtable -> dataAlloc = &DynamicArray_data_alloc_int;
        int_vtable -> toString = &toStringInt;
        int_vtable -> compare = &compareInt;
        int_vtable -> getType = &getTypeInt;
    }

    return int_vtable;
}

DynamicArray_vtable_t* get_float_DynamicArray_vtable() {
    if (float_vtable == NULL) {
        float_vtable = (DynamicArray_vtable_t*) malloc(sizeof(DynamicArray_vtable_t));
        float_vtable -> dataAlloc = &DynamicArray_data_alloc_float;
        float_vtable -> toString = &toStringFloat;
        float_vtable -> compare = &compareFloat;
        float_vtable -> getType = &getTypeFloat;
    }

    return float_vtable;
}


DynamicArray_vtable_t* get_string_DynamicArray_vtable() {
    if (string_vtable == NULL) {
        string_vtable = (DynamicArray_vtable_t*) malloc(sizeof(DynamicArray_vtable_t));
        string_vtable -> dataAlloc = &DynamicArray_data_alloc_string;
        string_vtable -> toString = &toStringString;
        string_vtable -> compare = &compareString;
        string_vtable -> getType = &getTypeString;
    }

    return string_vtable;
}



char* toString(DynamicArray_t* da) {
    return da -> funcs -> toString(da);
}


char* toStringInt(DynamicArray_t* da) {
    char* buff = (char*) malloc(da -> data -> count * (12 + 2) + 5);
    if (da -> data -> count == 0) {
        sprintf(buff, "[]");
        return buff;
    }

    char* current = buff;
    current += sprintf(current, "[ ");
    for (int i = 0; i < da -> data -> count - 1; ++i) {
        current += sprintf(current, "%i, ", *(int*)getElementVoid(da, i));
    }
    sprintf(current, "%i ]", *(int*)getElementVoid(da, da -> data -> count - 1));

    return buff;
}


char* toStringFloat(DynamicArray_t* da) {
    char* buff = (char*) malloc(da -> data -> count * (15 + 2) + 5);
    if (da -> data -> count == 0) {
        sprintf(buff, "[]");
        return buff;
    }

    char* current = buff;
    current += sprintf(current, "[ ");
    for (int i = 0; i < da -> data -> count - 1; ++i) {
        current += sprintf(current, "%f, ", *(float*)getElementVoid(da, i));
    }
    sprintf(current, "%f ]", *(float*)getElementVoid(da, da -> data -> count - 1));

    return buff;
}


char* toStringString(DynamicArray_t* da) {
    int buffSz = 3;

    for (int i = 0; i < da -> data -> count; ++i) {
        char* str = getElementVoid(da, i);
        buffSz += strlen(str) + 4;
    }
    
    char* buff = (char*)malloc(buffSz);

    if (da -> data -> count == 0) {
        sprintf(buff, "[]");
        return buff;
    }

    char* curBuff = buff;
    curBuff += sprintf(curBuff, "[ ");
    for (int i = 0; i < da -> data -> count - 1; ++i) {
        char* str = getElementVoid(da, i);
        curBuff += sprintf(curBuff, "\"%s\", ", str);
    }

    char* str = (char*)getElementVoid(da, da->data->count - 1);
    sprintf(curBuff, "\"%s\" ]", str);

    return buff;
}


void resize(DynamicArray_t* da, int size) {
    if (size == da -> data -> capacity) {
        return;
    }

    void* new_array = malloc(getCapacity(size) * da -> data -> elementSize);

    int elementsToCopy = (da -> data -> count < size) ? da -> data -> count : size;
    memcpy(new_array, da -> data -> array, elementsToCopy * da -> data -> elementSize);

    free(da -> data -> array);

    da -> data -> count = elementsToCopy;
    da -> data -> capacity = getCapacity(size);
    da -> data -> array = new_array;
}


void* getElementVoid(DynamicArray_t* da, int idx) {
    void* element = malloc(da -> data -> elementSize);

    memcpy(element, (char *)da -> data -> array + idx * da -> data -> elementSize, da -> data -> elementSize);
    
    return element;
}


void setVoidElement(DynamicArray_t* da, void* val, int idx) {
    char* byte = (char *)da -> data -> array;
    
    void* element_ptr = byte + idx * da -> data -> elementSize;

    memcpy(element_ptr, val, da -> data -> elementSize);
}


void pushBackVoid(DynamicArray_t* da, void* val) {
    if (da -> data -> count == da -> data -> capacity) {
        resize(da, da -> data -> capacity * 2);
    }

    setVoidElement(da, val, da -> data -> count);
    da -> data -> count++;
}


int getLenght(DynamicArray_t* da) {
    return da -> data -> count;
}


bool compare(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2) {
    return da1 -> funcs -> compare(da1, idx1, da2, idx2);
}


bool compareInt(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2) {
    int a = *(int *)getElementVoid(da1, idx1);
    int b = *(int *)getElementVoid(da2, idx2);
    return (a < b);
}


bool compareFloat(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2) {
    int a = *(float *)getElementVoid(da1, idx1);
    int b = *(float *)getElementVoid(da2, idx2);
    return (a < b);
}

bool compareString(DynamicArray_t* da1, int idx1, DynamicArray_t* da2, int idx2) {
    char* str1 = (char *)getElementVoid(da1, idx1);
    char* str2 = (char *)getElementVoid(da2, idx2);

    int str1SZ = strlen(str1);
    int str2SZ = strlen(str2);

    free(str1);
    free(str2);

    return str1SZ < str2SZ;
}


DynamicArray_t* concatenateDynamicArrays(DynamicArray_t* da1, DynamicArray_t* da2) {
    DynamicArray_t* new_da = new_DynamicArray(da1 -> funcs, da1 -> data -> count + da2 -> data -> count, da1 -> data -> elementSize);
    
    int szda1 = da1 -> data -> count * da1 -> data -> elementSize;
    int szda2 = da2 -> data -> count * da2 -> data -> elementSize;
    memcpy(new_da -> data -> array, da1 -> data -> array, szda1);
    memcpy((char *)new_da -> data -> array + szda1, da2 -> data -> array, szda2);

    /*for (int i = 0; i < da1 -> data -> count; ++i) {
        setVoidElement(new_da, getElementVoid(da1, i), i);
    }

    for (int i = 0; i < da2 -> data -> count; ++i) {
        setVoidElement(new_da, getElementVoid(da2, i), da1 -> data -> count + i);
    }*/
    
    return new_da;
}

DynamicArray_t* merge(DynamicArray_t* da1, DynamicArray_t* da2) {
    DynamicArray_t* ret = new_DynamicArray(da1 -> funcs, da1 -> data -> count + da2 -> data -> count, da1 -> data -> elementSize);

    int da1_count = da1 -> data -> count;
    int da2_count = da2 -> data -> count;
    int i = 0, j = 0;
    while (i < da1_count || j < da2_count) {
        if (j == da2_count || (i != da1_count && compare(da1, i, da2, j))) {
            setVoidElement(ret, getElementVoid(da1, i), i + j);
            ++i;
        } else {
            setVoidElement(ret, getElementVoid(da2, j), i + j);
            ++j;
        }
    }

    freeDynamicArray(da1);
    freeDynamicArray(da2);

    return ret;
}


DynamicArray_t* mergeSort(DynamicArray_t* da) {
    if (da -> data -> count == 1) {
        return da;
    }

    int mid = da -> data -> count / 2;
    DynamicArray_t* dal = new_DynamicArray(da -> funcs, mid, da -> data -> elementSize);
    DynamicArray_t* dar = new_DynamicArray(da -> funcs, da -> data -> count - mid, da -> data -> elementSize);

    int szdal = mid * da -> data -> elementSize;
    int szdar = dar -> data -> count * da -> data -> elementSize;
    
    memcpy(dal -> data -> array, da -> data -> array, szdal);
    memcpy(dar -> data -> array, (void *)((char *)da -> data -> array + szdal), szdar);

    /*for (int i = 0; i < mid; ++i) {
        setVoidElement(dal, getElementVoid(da, i), i);
    }

    for (int i = 0; i < da -> data -> count - mid; ++i) {
        setVoidElement(dar, getElementVoid(da, mid + i), i);
    }*/

    dal = mergeSort(dal);
    dar = mergeSort(dar);

    return merge(dal, dar);
}

DynamicArray_t* mapDynamicArray(DynamicArray_t* da, MapFunctionUnion_t* func) {
    DynamicArray_t* new_da = new_DynamicArray(da -> funcs, da -> data -> count, da -> data -> elementSize);

    switch (da -> funcs -> getType())
    {
    case INT:
        for (int i = 0; i < da -> data -> count; ++i) {
            int nelement = func -> MapFunctionInt(change_void_to_int(getElementVoid(da, i)));
            setVoidElement(new_da, change_to_void(nelement), i);
        }
        break;
    case FLOAT:
        for (int i = 0; i < da -> data -> count; ++i) {
            float nelement = func -> MapFunctionFloat(change_void_to_float(getElementVoid(da, i)));
            setVoidElement(new_da, change_to_void(nelement), i);
        }
        break;
    case STRING:
        
    default:
        break;
    }

    return new_da;
}


DynamicArray_t* whereDynamicArray(DynamicArray_t* da, WhereFunctionUnion_t* func) {
    DynamicArray_t* new_da = new_DynamicArray(da -> funcs, 0, da -> data -> elementSize);

    switch (da -> funcs -> getType())
    {
    case INT:
        for (int i = 0; i < da -> data -> count; ++i) {
            if (func -> WhereFunctionInt(change_void_to_int(getElementVoid(da, i)))) {
                pushBackVoid(new_da, getElementVoid(da, i));
            }
        }
        break;
    case FLOAT:
        for (int i = 0; i < da -> data -> count; ++i) {
            if (func -> WhereFunctionFloat(change_void_to_float(getElementVoid(da, i)))) {
                pushBackVoid(new_da, getElementVoid(da, i));
            }
        }
        break;
    default:
        break;
    }

    return new_da;
}


void* reduceDynamicArray(DynamicArray_t* da, ReduceFunctionUnion_t* func) {
    void* ret = malloc(da -> data -> elementSize);
    memcpy(ret, getElementVoid(da, 0), da -> data -> elementSize);

    switch (da -> funcs -> getType())
    {
    case INT:
        for (int i = 1; i < da -> data -> count; ++i) {
            int* midRet = (int *)ret;
            *midRet = func -> ReduceFunctionInt(change_void_to_int(getElementVoid(da, i)), *midRet);
        }
        break;
    case FLOAT:
        for (int i = 1; i < da -> data -> count; ++i) {
            float* midRet = (float *)ret;
            *midRet = func -> ReduceFunctionFloat(change_void_to_float(getElementVoid(da, i)), *midRet);
        }
        break;
    default:
        break;
    }

    return ret;
}