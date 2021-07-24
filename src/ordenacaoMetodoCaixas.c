#include <stdlib.h>

#include "ordenacaoMetodoCaixas.h"

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
            array[j] = i +minValue;
            // diminui a contagem da caixa
            caixas[i] = caixas[i] -1;
            // avança uma posição no array
            j = j +1;
        }
    }
}