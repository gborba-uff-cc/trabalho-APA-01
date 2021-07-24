#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "tests.h"
#include "util.h"
#include "heapsort.h"
#include "ordenacaoMetodoCaixas.h"

/** Testa se o heapsort está ordenando em ordem crescente */
bool testHeapsort()
{
    int size = 0;
    int round = 0;
    bool isOrdered = false;
    int *array = NULL;

    for (size = 5; size < 50; size+=5) {
        array = generateRandomIntArray(array, size, 0, 1000, time(NULL));
        if (array == NULL) {
            printf("Não foi possível criar um array para a realização de testes");
            exit(1);
        }
        for (round = 0; round < 5; round++) {
            heapsort(array, size);
            isOrdered = testAscendingOrder(array, size);
            if (isOrdered == false) {
                return false;
            }
        }
    }
    return true;
}

bool testOrdenacaoMetodoCaixas()
{
    int *array = NULL;
    int size = 0;
    int minValue = 0;
    int maxValue = 1000;
    int round = 0;
    bool isOrdered = false;

    for (size = 5; size < 50; size+=5) {
        array = generateRandomIntArray(array, size, minValue, maxValue, time(NULL));
        if (array == NULL) {
            printf("Não foi possível criar um array para a realização de testes");
            exit(1);
        }
        for (round = 0; round < 5; round++) {
            ordenacaoMetodoCaixas(array, size, minValue, maxValue);
            isOrdered = testAscendingOrder(array, size);
            if (isOrdered == false) {
                return false;
            }
        }
    }
    return true;
}

bool testAscendingOrder(int *array, int n)
{
    if (array == NULL) {
        return false;
    }
    else if (n == 1) {
        return true;
    }
    else {
        int i;
        for (i = 1; i < n-1; i++) {
            if (array[i] > array[i+1]) {
                return false;
            }
        }
    }
    return true;
}