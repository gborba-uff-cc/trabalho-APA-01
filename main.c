#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/resource.h>

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

// ordenacaoMetodoCaixas.h -----------------------------------------------------
/** Ordena, em ordem ordem crescente, um array de inteiros com n elementos.
 *
 * obs.: Os elementos devem pertecer ao intervalo [a,b]
 *
 * obs.: A ordenação é feita usando o método das caixas (método das caixas é um 
 * caso particular do bucket sort);
 */
void ordenacaoMetodoCaixas();

// ordenacaoMetodoCaixas.h -----------------------------------------------------
void ordenacaoMetodoCaixas(int *array, int n, int minValue, int maxValue)
{
    if (array == NULL) {
        return;
    }
    int nCaixas = maxValue -minValue +1;
    int caixas[nCaixas];
    int i = 0;
    int j = 0;

    // para cada caixa
    for (i = 0; i < nCaixas; i++) {
        // inicializa a posição com 0
        caixas[i] = 0;
    }

    // contabiliza o total de elementos de cada valor que existe no array
    for (i = 0; i < n; i++) {
        // aumenta a contagem na caixa correspondente ao elemento no array[i]
        caixas[array[i] -minValue] = caixas[array[i] -minValue] +1;
    }

    // para cada caixa
    for (i = 0, j = 0; i < nCaixas; i++) {
        // enquanto a caixa não estiver vazia
        while (caixas[i] != 0) {
            // coloca o elemento na posição correta
            array[j] = j +minValue;
            // diminui a contagem da caixa
            caixas[i] = caixas[i] -1;
            // avança uma posição no array
            j = j +1;
        }
    }
}

// util.h ----------------------------------------------------------------------
/** Testa se o heapsort está ordenando em ordem crescente */
bool testHeapsort();

/** Testa se a ordenação pelo método das caixas está ordenando em ordem crescente */
bool testOrdenacaoMetodoCaixas();

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

/** função auxiliar que nos foi fornecida para calcular o tempo de CPU */
void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total);

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

int *generateRandomIntArray(
    int *array, int newArraySize, 
    int lowerValue, int upperValue, 
    unsigned int seed)
{
    if (array != NULL) {
        free(array);
        array = NULL;
    }
    array = (int *) malloc(sizeof(int) * newArraySize);
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

void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total)
{
    long seg_CPU, seg_sistema, mseg_CPU, mseg_sistema;
    struct rusage ptempo;

    getrusage(0,&ptempo);

    seg_CPU = ptempo.ru_utime.tv_sec;
    mseg_CPU = ptempo.ru_utime.tv_usec;
    seg_sistema = ptempo.ru_stime.tv_sec;
    mseg_sistema = ptempo.ru_stime.tv_usec;

    *seg_CPU_total     = (seg_CPU + 0.000001 * mseg_CPU);
    *seg_sistema_total = (seg_sistema + 0.000001 * mseg_sistema);
}

// main.c ----------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    printf(
        testHeapsort() 
        ? "Teste do Heapsort: Sucesso\n" 
        : "Teste do Heapsort: Falhou\n");
    printf("\n");
    printf(
        testOrdenacaoMetodoCaixas() 
        ? "Teste da ordenacao pelo método caixas: Sucesso\n" 
        : "Teste da ordenacao pelo método caixas: Falhou\n");
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
    int repetitionsPerArray = 1000; // deve ser maior que 0
    int a = 0;
    int b = 0;
    int c = 0;
    bool isOrdered = false;
    double t_cpu_start = 0.0;
    double t_cpu_finish = 0.0;
    double dt_cpu = 0.0;
    double dt_cpu_acc = 0.0;
    double dt_cpu_meanPerSize = 0.0;
    double t_kernel_start = 0.0;
    double t_kernel_finish = 0.0;
    double dt_kernel = 0.0;
    double dt_kernel_acc = 0.0;
    double dt_kernel_meanPerSize = 0.0;

    // para cada um dos tamanhos de array
    for (a = 0; a < nArraySizes; a++) {
        arraySize = arraySizes[a];
        dt_cpu_acc = 0.0;
        dt_kernel_acc = 0.0;
        // para cada tamanho de array, gera um array usando uma das seeds
        for (b = 0; b < nArraySeeds; b++) {
            arraySeed = arraySeeds[b];
            // realiza x repetições para cada par de tamanho e seed do array
            for (c = 0; c < repetitionsPerArray; c++) {
                array = generateRandomIntArray(
                    array, arraySize, elemMinValue, elemMaxValue, arraySeed);
                if (array == NULL) {
                    printf("Abortando programa...\nNão foi possível gerar o array de tamanho %d com a seed %d.\n",
                        arraySize, arraySeed);
                    exit(1);
                }
                // toma tempo de cpu e de kernel
                Tempo_CPU_Sistema(&t_cpu_start, &t_kernel_start);
                heapsort(array, arraySize);
                Tempo_CPU_Sistema(&t_cpu_finish, &t_kernel_finish);

                // computa o tempo de cpu
                dt_cpu = t_cpu_finish - t_cpu_start;
                dt_cpu_acc += dt_cpu;
                dt_kernel = t_kernel_finish - t_kernel_start;
                dt_kernel_acc += dt_kernel;

                // // apresenta tempos parciais
                // printf("Heapsort para o array de tamanho: %d, gerado com a seed: %d.\n    Tempo total CPU: %f\n    Tempo total kernel: %f\n",
                //     arraySize, arraySeed, dt_cpu, dt_kernel);
                // printf("\n");
            }
        }
        dt_cpu_meanPerSize = dt_cpu_acc / (nArraySeeds * repetitionsPerArray);
        dt_kernel_meanPerSize = dt_cpu_acc / (nArraySeeds * repetitionsPerArray);

        // apresenta tempos médios
        printf("Heapsort para o array de tamanho: %d. (%d repetições realizadas)\n    Tempo médio total CPU: %f\n    Tempo médio total kernel: %f\n",
            arraySize, nArraySeeds * repetitionsPerArray, 
            dt_cpu_meanPerSize, dt_kernel_meanPerSize);
        printf("\n");
    }
    return 0;
}