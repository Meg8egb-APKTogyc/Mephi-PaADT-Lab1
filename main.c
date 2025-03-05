#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.c"

/*
норма матрицы ||A|| - норма в линейном пространстве матриц
норма матрицы - это неотрицательне вещественное число обладающее некторым количеством свойств:
1. Если матрица ненулевая, то ее норма больше 0. Равна 0, если матрица нулевая
2. Норма суммы матриц A и B >= сумме норм матриц A и B
3. Если матрица умножается на число, то норма умножается на число

Можно ввести абсолютно любую норму матриц, но существует несколько норм.
1. Сумма всех коэффициентов матрицы по модулю
2.1 M-норма - Суммируем все элементы по модулю ПОСТРОЧНО и называем нормой маскимальную вычисленную сумму
2.1 L-норма - Суммируем все элементы по модулю ПОСТОЛБНО и называем нормой маскимальную вычисленную сумму
3. K-норма - корень из суммы квадратов всех элементов матрицы


Число обусловленности матрицы(мера обусловленности матрицы):
cond(A) - это произведение норм матрицы и обратной матрицы (||A|| * ||A^-1||)

Матрицы у которых cond(A) большое называют плохо обусловленными
Матрицы у которых cond(A) маленькое называют хорошо обусловленными

Число обусловленности матрицы при решении линейных уравненний связано с погрешностью результата

ДЗ:
Для матрицы Глильберта(3*3) посчитать обратную по методу Гаоса и посчитать для нее число обусловленности матрицы, используя K-норму
*/


float multipyByTwo(float a) {
    return a * 2;
}

bool isOdd(float a) {
    return a > 15;
}


float sum(float a, float b) {
    return a + b;
}


int main() {
    DynamicArray_t* da = new_DynamicArray(get_string_DynamicArray_vtable(), 4, 10);
    DynamicArray_t* da2 = new_DynamicArray(get_string_DynamicArray_vtable(), 3, 10);
    char* a = "bebra";
    char* b = "pensil";
    char* c = "chinchon";
    char* d = "loli";

    setVoidElement(da, (void *)a, 0);
    setVoidElement(da, (void *)b, 2);

    setVoidElement(da2, (void *)c, 0);
    setVoidElement(da2, (void *)d, 2);

    char* sda = toString(da2);

    char* elem = (char *)getElementVoid(da, 1);
    puts(sda);
    puts(elem);

    DynamicArray_t* cda = concatenateDynamicArrays(da, da2);
    char* scda = toString(cda);
    puts(scda);

    DynamicArray_t* socda = mergeSort(cda);
    char* ssocda = toString(socda);
    puts(ssocda);

    /*DynamicArray_t* da = newDynamicArray(get_float_DynamicArray_vtable(), 4);
    DynamicArray_t* da2 = newDynamicArray(get_float_DynamicArray_vtable(), 4);

    float *a = malloc(sizeof(float));
    float *b = malloc(sizeof(float));
    *a = 11.1f;
    *b = 22.2f;

    setVoidElement(da, (void *)a, 0);
    setVoidElement(da, (void *)b, 1);

    *a = 123.3f;

    float* c = malloc(sizeof(float)); 
    c = (float *)getElementVoid(da, 1);
    *c = 3332.4f;

    setVoidElement(da2, (void *)a, 0);
    setVoidElement(da2, (void *)a, 1);

    DynamicArray_t* nda = concatenateDynamicArrays(da, da2);

    char* sda = toString(da);
    puts(sda);

    char* nsda = toString(nda);
    puts(nsda);

    char* ssda = toString(mergeSort(nda));
    puts(ssda);

    setVoidElement(da2, (void *)b, 3);

    char* sda2 = toString(da2);
    puts(sda2);

    ssda = toString(mergeSort(nda));
    puts(ssda);


    MapFunctionUnion_t funcMap;
    funcMap.MapFunctionFloat = multipyByTwo;
    DynamicArray_t* mapda = mapDynamicArray(nda, &funcMap);

    char* smapda = toString(mapda);
    puts(smapda);

    WhereFunctionUnion_t funcWhere;
    funcWhere.WhereFunctionFloat = isOdd;
    DynamicArray_t* wheda = whereDynamicArray(nda, &funcWhere);
    pushBack(wheda, 10);

    char* swheda = toString(wheda);
    puts(swheda);

    ReduceFunctionUnion_t funcRed;
    funcRed.ReduceFunctionFloat = sum;
    void* redVal = reduceDynamicArray(wheda, &funcRed);

    printf("%f\n", *(float *)redVal);

    printf("%f \n", *c);

    printf("%i \n", getLenght(da));*/

    return EXIT_SUCCESS;
}
