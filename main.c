#include <stdio.h>;
#include <stdlib.h>;

// heapsort.h ------------------------------------------------------------------
void heapsort(int *array, int n);
void heapify(int *array, int n);
void deleteMax(int *array, int n);
void bubbleDown(int *array, int i, int n);
void swap(int *array, int i, int j);

// heapsort.c ------------------------------------------------------------------
/** encontra a posição correta para o valor atualmente em i */
void bubbleDown(int *array, int i, int n) {
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

//* troca o elemento na posição i com o elemento na posição j */
void swap(int *array, int i, int j) {
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

