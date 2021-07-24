#ifndef __UTIL_H_FILE__
#define __UTIL_H_FILE__

/** 
 * Tenta gerar dinâmicamente um novo array com n inteiros.
 *
 * obs.: Deve testar se foi possível criar o novo array
*/
int *generateRandomIntArray(
    int *array, int newArraySize, 
    int lowerValue, int upperValue, 
    unsigned int seed);

/**
 * Imprime no terminal os elementos de índice 0 até n do array de inteiros.
 *
 * obs.: imprime um elemento após o outro sem quebra de linha;
 */
void printIntArray(int *array, int n);

/** função auxiliar que nos foi fornecida para calcular o tempo de CPU */
void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total);

#endif