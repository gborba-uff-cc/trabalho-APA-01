#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#include "util.h"

int main(int argc, char const *argv[])
{
    // valores padrão
    int elemMinValue = 0;
    int elemMaxValue = 1000;
    int arraySizeStep = 100;
    int arraySizeMinimum = 1000;
    int arraySizeMaximum = 25000;
    const int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    const int nArraySeeds = sizeof(arraySeeds)/sizeof(int);

    int *array = NULL;
    int arraySize = 0;
    int arraySeed = 0;
    int maxValue = 0;

    char fileName[100];
    int arraysCount = 0;
    time_t startTime = time(NULL);
    char todayDate[20];

    // interage com o usuario --------------------------------------------------
    bool paramsAreValids = true;
    // tenta pegar parametros via argumentos do programa
    if (getParamsFromArgs(argc, argv, &arraySizeMinimum, &arraySizeMaximum,
        &arraySizeStep, &elemMinValue, &elemMaxValue)) {
    }
    // tenta pegar parametros do terminal, se não conseguiu via argumentos
    else if (getParamsFromTerminal(&arraySizeMinimum, &arraySizeMaximum,
        &arraySizeStep, &elemMinValue, &elemMaxValue)) {
    }
    // usa valores padrão se não não ceonseguiu pegar parametros de outras formas
    // faz validação parametros
    paramsAreValids &= (0 <= arraySizeMinimum && arraySizeMinimum <= arraySizeMaximum);
    paramsAreValids &= (0 <= arraySizeMaximum && arraySizeMaximum <= INT_MAX - 1);
    paramsAreValids &= (INT_MIN <= arraySizeStep && arraySizeStep <= INT_MAX);
    paramsAreValids &= (INT_MIN <= elemMinValue && elemMinValue <= INT_MAX);
    paramsAreValids &= (INT_MIN <= elemMaxValue && elemMaxValue <= INT_MAX);
    if (paramsAreValids == false) {
        puts("Nenhum dos valores fornecidos são válidos");
        return 1;
    }

    // apresenta os parametros que serão usados no programa
    printf(
"Valores que serão usados para gerar os arrays:\n\
    tamanho mínimo:   %d\n\
    tamanho máximo:   %d\n\
    tamanho do passo: %d\n\
    valor mínimo:     %d\n\
    valor máximo:     %d\n",
        arraySizeMinimum, arraySizeMaximum, arraySizeStep,
        elemMinValue, elemMaxValue);
    fputs("", stdout);

    int i = 0;
    for (arraySize = arraySizeMinimum; arraySize <= arraySizeMaximum; arraySize += arraySizeStep) {
        maxValue = elemMaxValue;
        for (i = 0; i < nArraySeeds; i++) {
            arraySeed = arraySeeds[i];
            array = generateRandomIntArray(array, arraySize, elemMinValue, maxValue, arraySeed);

            if (array == NULL) {
                continue;
            }
            ++arraysCount;

            getStrDateTime(todayDate, &startTime);
            sprintf(fileName, "./generatedArrays/%s_%d.txt", todayDate, arraysCount);
            persistIntArray(fileName, array, arraySize, elemMinValue, maxValue);
        }
    }
    return 0;
}

// lê array salvo no arquivo
// int *arrayLido = NULL, nLido = 0, minValorLido = 0, maxValorLido = 0;
// char inputFilename[100];
// sprintf(inputFilename, "./generatedArrays/%s_%d.txt", todayDate, 1);
// arrayLido = readIntArrayFromFile(inputFilename, arrayLido, &nLido, &minValorLido, &maxValorLido);
// if (arrayLido != NULL) {
//     printf("Número de elementos:%d, Valor Mínimo: %d, Valor Máximo: %d\n", nLido, minValorLido, maxValorLido);
//     printIntArray(arrayLido, nLido);
// }