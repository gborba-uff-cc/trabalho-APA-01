#include <stdio.h>
#include <stdlib.h>

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
    int i;
    heapify(array, n);
    for (i = n; i > 0; i--) {
        deleteMax(array, i);
    }
    return;
}

void heapify(int *array, int n)
{
    int i;
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
    n = n-2;
    // reorganiza o heap colocando a raiz na posição certa
    bubbleDown(array, 0, n);
    return;
}

void bubbleDown(int *array, int i, int n)
{
    int filho;
    // indice do primeiro filho (da esquerda)
    filho = 2*i +1;
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
    int temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    return;
}

// -----------------------------------------------------------------------------
int main(int argc, char const *argv[]) {
    printf("Ola mundo");
    return 0;
}

