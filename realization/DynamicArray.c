#include "../headers/DynamicArray.h"


int _getCapacity(int size) {
    int bit = 1;
    while (bit <= size)
        bit = (bit << 1);

    return bit;
}


DynamicArray_t* new_DynamicArrayEr(Types_vtable_t* funcs, int size, int elemSize, DA_ErrorCode* error) {
    if (error) *error = EH_OK;

    RETURN_IF_ERROR(!funcs || size < 0 || elemSize <= 0, EH_ERROR_INVALID_INPUT, NULL);
    DynamicArray_t* da = (DynamicArray_t*) malloc(sizeof(DynamicArray_t));
    RETURN_IF_ERROR(!da, EH_ERROR_MEMORY_ALLOCATION, NULL);
    da -> data = (DynamicArray_data_t*) malloc(sizeof(DynamicArray_data_t));
    if (!da->data) {
        free(da);
        RETURN_IF_ERROR(1, EH_ERROR_MEMORY_ALLOCATION, NULL);
    }

    da -> funcs = (Types_vtable_t*) malloc(sizeof(Types_vtable_t));
    if (!da -> funcs) {
        free(da);
        free(da->data);
        RETURN_IF_ERROR(1, EH_ERROR_MEMORY_ALLOCATION, NULL);
    }
    da -> funcs = funcs;
    da -> data -> count = size;
    da -> data -> capacity = _getCapacity(size);
    da -> data -> elementSize = elemSize;
    da -> data -> array = dataAlloc(da -> funcs, da -> data -> count, da -> data -> capacity, da -> data -> elementSize);

    return da;
}


char* DAtoStringEr(DynamicArray_t* da, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    int buffSz = 3;

    for (int i = 0; i < da -> data -> count; ++i) {
        char* str = toString(da -> funcs, getElementVoidEr(da, i, error), da -> data -> elementSize);

        buffSz += strlen(str) + 4;
    }
    
    char* buff = (char*)malloc(buffSz);

    if (da -> data -> count == 0) {
        sprintf(buff, "[]");
        return buff;
    }

    char* curBuff = buff;
    curBuff += sprintf(curBuff, "[ ");
    for (int i = 0, n = da -> data -> count; i < n; ++i) {
        char* str = toString(da -> funcs, getElementVoidEr(da, i, error), da -> data -> elementSize);
        curBuff += sprintf(curBuff, "\"%s\"", str);

        if (i + 1 == n)
            curBuff += sprintf(curBuff, " ]");
        else
            curBuff += sprintf(curBuff, ", ");
    }

    if (error) *error = EH_OK;

    return buff;
}


ErrorCode* freeDynamicArrayEr(DynamicArray_t* da, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

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


ErrorCode* resizeEr(DynamicArray_t* da, int size, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    if (size == da -> data -> capacity) {
        da -> data -> count = size;
        return NULL;
    }

    void* new_array = malloc(_getCapacity(size) * da -> data -> elementSize);
    RETURN_IF_ERROR(!new_array, EH_ERROR_MEMORY_ALLOCATION, NULL);

    int elementsToCopy = (da -> data -> count < size) ? da -> data -> count : size;
    memcpy(new_array, da -> data -> array, elementsToCopy * da -> data -> elementSize);

    free(da -> data -> array);

    da -> data -> count = size;
    da -> data -> capacity = _getCapacity(size);
    da -> data -> array = new_array;
}


void* getElementVoidEr(DynamicArray_t* da, int idx, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);
    RETURN_IF_ERROR(idx < 0 || idx >= da -> data -> count, EH_ERROR_INDEX_OUT_OF_RANGE, NULL);

    void* element = malloc(da -> data -> elementSize);

    memcpy(element, (char *)da -> data -> array + idx * da -> data -> elementSize, da -> data -> elementSize);
    
    return element;
}


ErrorCode* setVoidElementEr(DynamicArray_t* da, void* val, int idx, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);
    RETURN_IF_ERROR(idx < 0 || idx >= da -> data -> count, EH_ERROR_INDEX_OUT_OF_RANGE, NULL);

    char* byte = (char *)da -> data -> array;
    
    void* element_ptr = byte + idx * da -> data -> elementSize;

    memcpy(element_ptr, val, da -> data -> elementSize);
}


ErrorCode* pushBackVoidEr(DynamicArray_t* da, void* val, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    if (da -> data -> count == da -> data -> capacity) {
        resizeEr(da, da -> data -> count + 1, error);
        setVoidElementEr(da, val, da -> data -> count - 1, error);
        return NULL;
    }

    da -> data -> count++;
    setVoidElementEr(da, val, da -> data -> count - 1, error);
}


ErrorCode* popBackEr(DynamicArray_t* da, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    da -> data -> count--;
    return NULL;
}


int getLenghtEr(DynamicArray_t* da, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR_TYPE(!da, EH_ERROR_NULL_POINTER, int, 0);

    return da -> data -> count;
}


DynamicArray_t* concatenateDynamicArraysEr(DynamicArray_t* da1, DynamicArray_t* da2, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da1, EH_ERROR_NULL_POINTER, NULL);
    RETURN_IF_ERROR(!da2, EH_ERROR_NULL_POINTER, NULL);

    DynamicArray_t* new_da = new_DynamicArrayEr(da1 -> funcs, da1 -> data -> count + da2 -> data -> count, da1 -> data -> elementSize, error);
    
    int szda1 = da1 -> data -> count * da1 -> data -> elementSize;
    int szda2 = da2 -> data -> count * da2 -> data -> elementSize;
    memcpy(new_da -> data -> array, da1 -> data -> array, szda1);
    memcpy((char *)new_da -> data -> array + szda1, da2 -> data -> array, szda2);
    
    return new_da;
}

DynamicArray_t* mergeEr(DynamicArray_t* da1, DynamicArray_t* da2, VoidFunctionSort func, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da1, EH_ERROR_NULL_POINTER, NULL);
    RETURN_IF_ERROR(!da2, EH_ERROR_NULL_POINTER, NULL);

    DynamicArray_t* ret = new_DynamicArrayEr(da1 -> funcs, da1 -> data -> count + da2 -> data -> count, da1 -> data -> elementSize, error);

    if (func == NULL)
        func = da1 -> funcs -> compare;

    int da1_count = da1 -> data -> count;
    int da2_count = da2 -> data -> count;
    int i = 0, j = 0;
    while (i < da1_count || j < da2_count) {
        if (j == da2_count || (i != da1_count && func(getElementVoidEr(da1, i, error), getElementVoidEr(da2, j, error)))) {
            setVoidElementEr(ret, getElementVoidEr(da1, i, error), i + j, error);
            ++i;
        } else {
            setVoidElementEr(ret, getElementVoidEr(da2, j, error), i + j, error);
            ++j;
        }
    }

    freeDynamicArrayEr(da1, error);
    freeDynamicArrayEr(da2, error);

    return ret;
}


DynamicArray_t* mergeSortEr(DynamicArray_t* da, VoidFunctionSort func, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    if (da -> data -> count == 1) {
        return da;
    }

    int mid = da -> data -> count / 2;
    DynamicArray_t* dal = new_DynamicArrayEr(da -> funcs, mid, da -> data -> elementSize, error);
    DynamicArray_t* dar = new_DynamicArrayEr(da -> funcs, da -> data -> count - mid, da -> data -> elementSize, error);

    int szdal = dal -> data -> count * da -> data -> elementSize;
    int szdar = dar -> data -> count * da -> data -> elementSize;
    
    memcpy(dal -> data -> array, da -> data -> array, szdal);
    memcpy(dar -> data -> array, (void *)((char *)da -> data -> array + szdal), szdar);

    dal = mergeSortEr(dal, func, error);
    dar = mergeSortEr(dar, func, error);

    return mergeEr(dal, dar, func, error);
}

DynamicArray_t* mapDynamicArrayEr(DynamicArray_t* da, VoidFunctionMap func, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    DynamicArray_t* new_da = new_DynamicArrayEr(da -> funcs, da -> data -> count, da -> data -> elementSize, error);

    for (int i = 0; i < da -> data -> count; ++i) {
        setVoidElementEr(new_da, func(getElementVoidEr(da, i, error)), i, error);
    }

    return new_da;
}


DynamicArray_t* whereDynamicArrayEr(DynamicArray_t* da, VoidFunctionWhere func, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    DynamicArray_t* new_da = new_DynamicArrayEr(da -> funcs, 0, da -> data -> elementSize, error);

    for (int i = 0; i < da -> data -> count; ++i) {
        if (func(getElementVoidEr(da, i, error))) {
            pushBackVoidEr(new_da, getElementVoidEr(da, i, error), error);
        }
    }

    return new_da;
}


void* reduceDynamicArrayEr(DynamicArray_t* da, VoidFunctionReduce func, DA_ErrorCode* error) {
    if (error) *error = EH_OK;
    RETURN_IF_ERROR(!da, EH_ERROR_NULL_POINTER, NULL);

    void* ret = malloc(da -> data -> elementSize);
    RETURN_IF_ERROR(!ret, EH_ERROR_MEMORY_ALLOCATION, NULL);

    memcpy(ret, getElementVoidEr(da, 0, error), da -> data -> elementSize);

    for (int i = 1; i < da -> data -> count; ++i) {
        ret = func(getElementVoidEr(da, i, error), ret);
    }

    return ret;
}