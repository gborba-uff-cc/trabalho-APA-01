#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "util.h"

int main(int argc, char const *argv[])
{
    const int elemMinValue = 0;
    const int elemMaxValue = 1000;
    // const int arraySizeStep = 500;
    // const int arraySizeMinimum = arraySizeStep;
    // const int arraySizeMaximum = INT_MAX - arraySizeStep;
    const int arraySizeStep = 100;
    const int arraySizeMinimum = 1000;
    const int arraySizeMaximum = 25000;
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

    int i = 0;
    for (arraySize = arraySizeMinimum; arraySize <= arraySizeMaximum; arraySize += arraySizeStep) {
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

// lê array 1 salvo no arquivo
// int *arrayLido = NULL, nLido = 0, minValorLido = 0, maxValorLido = 0;
// arrayLido = readIntArrayFromFile("./generatedArrays/1.txt", arrayLido, &nLido, &minValorLido, &maxValorLido);
// if (arrayLido != NULL) {
//     printf("%d, %d, %d\n", nLido, minValorLido, maxValorLido);
//     printIntArray(arrayLido, nLido);
// }