#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// heapsort.h ------------------------------------------------------------------
/** ordena em ordem crescente um array de inteiros com n elementos*/
void heapsort(int *array, int n);

// heapsort.c ------------------------------------------------------------------
/** monta completamente um heap a partir de um array */
void heapify(int *array, int n);
/** "remove" a raiz do heap e o reorganiza elegendo uma nova raiz */
void deleteMax(int *array, int n);
/** encontra a posição correta para o valor atualmente em i */
void bubbleDown(int *array, int i, int n);
/** troca o elemento na posição i com o elemento na posição j */
void swap(int *array, int i, int j);

void heapsort(int *array, int n)
{
    int i = 0;
    if (array == NULL) {
        return;
    }
    heapify(array, n);
    for (i = n; i > 0; i--) {
        deleteMax(array, i);
    }
    return;
}

void heapify(int *array, int n)
{
    int i = 0;
    // desde o último até o primeiro elemento pai no heap
    for (i = (n-1)/2; i >= 0; i--) {
        // reorganiza o heap colocando o elemento atual na posição certa
        bubbleDown(array, i, n);
    }
    return;
}

void deleteMax(int *array, int n)
{
    // troca o primeiro e o útimo elemento de lugar
    swap(array, 0, n-1);
    // diminui o tamanho do heap
    n = n-1;
    // reorganiza o heap colocando a raiz na posição certa
    bubbleDown(array, 0, n);
    return;
}

void bubbleDown(int *array, int i, int n)
{
    // indice do primeiro filho (da esquerda)
    int filho = 2*i +1;
    // se filho não é ultimo elemento do array
    if (filho < n-1) {
        // se valor do filho da direita > valor do filho da esquerda
        if (array[filho+1] > array[filho]) {
            // filho com maior valor passa a ser o indicado
            filho = filho+1;
        }
    }
    // se filho está dentro do array
    if (filho <= n-1) {
        // se 'meu' valor é menor que o valor do filho
        if (array[i] < array[filho]) {
            // troca de valor com o filho
            swap(array, i, filho);
            // encontra a posição correta para o valor do filho
            bubbleDown(array, filho, n);
        }
    }
    return;
}

void swap(int *array, int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    return;
}

// util.h ----------------------------------------------------------------------
/** Testa se o heapsort se o heapsort está ordenando em ordem crescente */
bool testHeapsort();

/** Testa se os elementos do array de inteiros estão em ordem crescente */
bool testAscendingOrder(int *array, int n);

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

// util.c ----------------------------------------------------------------------
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

int *generateRandomIntArray(
    int *array, int newArraySize, 
    int lowerValue, int upperValue, 
    unsigned int seed)
{
    if (array != NULL) {
        free(array);
        array = NULL;
    }
    array = malloc(newArraySize*sizeof(int));
    if (array == NULL) {
        return array;
    }
    else {
        srand(seed);
        int i;
        for (i = 0; i < newArraySize; i++) {
            array[i]= (rand() % (upperValue - lowerValue + 1)) + lowerValue;
        }
    }
    return array;
}

void printIntArray(int *array, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf(i < n-1 ? "%d " : "%d\n" , array[i]);
    }
}

// main.c ----------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    printf(
        testHeapsort() 
        ? "Teste do Heapsort: Sucesso\n" 
        : "Teste do Heapsort: Falhou\n");
    printf("\n");

    int *array = NULL;
    int elemMinValue = 0;
    int elemMaxValue = 1000;
    int arraySizes[] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
    int nArraySizes = sizeof(arraySizes)/sizeof(int);
    int arraySize = 0;
    int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    int nArraySeeds = sizeof(arraySeeds)/sizeof(int);
    int arraySeed = 0;
    int repetitionsPerArray = 5;
    int cpuElapsedTime = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    bool isOrdered = false;

    // para cada um dos tamanhos de array
    for (a = 0; a < nArraySizes; a++) {
        arraySize = arraySizes[a];
        // para cada tamanho de array, gera um array usando uma das seeds
        for (b = 0; b < nArraySeeds; b++) {
            arraySeed = arraySeeds[b];
            // realiza x repetições para cada par de tamanho e seed
            for (c = 0; c < repetitionsPerArray; c++) {
                array = generateRandomIntArray(
                    array, arraySize, elemMinValue, elemMaxValue, arraySeed);
                if (array == NULL) {
                    printf("Abortando programa...\nNão foi possível gerar o array de tamanho %d com a seed %d.\n",
                        arraySize, arraySeed);
                    return 1;
                }
                heapsort(array, arraySize);

                printf(
                    "Heapsort para o array de tamanho %d gerado com a seed %d levou %d para ser concluído.\n",
                    arraySize, arraySeed, cpuElapsedTime);
                printf("\n");
            }
        }
    }
    return 0;
}