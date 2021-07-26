#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "util.h"

int main(int argc, char const *argv[])
{
    const int elemMinValue = 0;
    const int elemMaxValue = 1000;
    const int arraySizeStep = 500;
    const int arraySizeMinimum = arraySizeStep;
    const int arraySizeMaximum = INT_MAX - arraySizeStep;
    const int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    const int nArraySeeds = sizeof(arraySeeds)/sizeof(int);

    int *array = NULL;
    int arraySize = 5;
    int arraySeed = 0;

    char fileName[100];
    int arraysCount = 0;

    int i = 0;
    for (arraySize = arraySizeMinimum; arraySize < arraySizeMaximum; arraySize += arraySizeStep) {
        for (i = 0; i < nArraySeeds; i++) {
            arraySeed = arraySeeds[i];
            array = generateRandomIntArray(array, arraySize, elemMinValue, elemMaxValue, arraySeed);

            if (array == NULL) {
                continue;
            }
            ++arraysCount;

            sprintf(fileName, "./generatedArrays/%d.txt", arraysCount);
            persistIntArray(fileName, array, arraySize, elemMinValue, elemMaxValue);
        }
    }
    return 0;
}

// lê array 1 salvo no arquivo
// int *arrayLido = NULL, nLido = 0, minValorLido = 0, maxValorLido = 0;
// arrayLido = readIntArrayFromFile("./generatedArrays/1.txt", arrayLido, &nLido, &minValorLido, &maxValorLido);
// if (arrayLido != NULL) {
//     printf("%d, %d, %d\n", nLido, minValorLido, maxValorLido);
//     printIntArray(arrayLido, nLido);
// }