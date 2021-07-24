#ifndef __TESTS_H_FILE__
#define __TESTS_H_FILE__

#include <stdbool.h>

/** Testa se o heapsort está ordenando em ordem crescente */
bool testHeapsort();

/** Testa se a ordenação pelo método das caixas está ordenando em ordem crescente */
bool testOrdenacaoMetodoCaixas();

/** Testa se os elementos do array de inteiros estão em ordem crescente */
bool testAscendingOrder(int *array, int n);

#endif