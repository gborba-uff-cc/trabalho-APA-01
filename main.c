#include <stdio.h>;
#include <stdlib.h>;

// heapsort.h ------------------------------------------------------------------
void heapsort(int *array, int n);
void heapify(int *array, int n);
void deleteMax(int *array, int n);
void bubbleDown(int *array, int i, int n);
void swap(int *array, int i, int j);

// heapsort.c ------------------------------------------------------------------
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

