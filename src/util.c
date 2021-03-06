#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/resource.h>
#include <time.h>

#include "util.h"

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

void persistIntArray(char *fileName, int *array, int n, int elemMinValue, int elemMaxValue)
{
    FILE *fp;
    int i;

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        return;
    }

    fprintf(fp, "%d %d %d\n", n, elemMinValue, elemMaxValue);
    for (i = 0; i < n; ++i) {
        fprintf(fp, i < (n-1) ? "%d\n" : "%d", array[i]);
    }

    fclose(fp);
}

int *readIntArrayFromFile(char *filename, int *array, int *n, int *elemMinValue, int *elemMaxValue)
{
    FILE *fp = NULL;
    char buffer[50];
    int numRead = 0;
    int newArraySize = 0;
    int minValue = 0;
    int maxValue = 0;
    int i = 0;

    // abre o arquivo
    fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }

    // lê o tamanho, o valor mínimo e valor máximo dos elementos do array
    if (fgets(buffer, sizeof(buffer), fp) != 0) {
        sscanf(buffer, "%d %d %d", &newArraySize, &minValue, &maxValue);
    } else {
        return NULL;
    }

    // cria novo array
    if (array != NULL) {
        free(array);
    }
    array = (int *) malloc(sizeof(int) * newArraySize);
    if (array == NULL) {
        return array;
    }

    // popula o array
    i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != 0) {
        sscanf(buffer, "%d", &numRead);
        array[i] = numRead;
        ++i;
    }

    // fecha o arquivo
    fclose(fp);

    *n = newArraySize;
    *elemMinValue = minValue;
    *elemMaxValue = maxValue;
    return array;
}

void getStrDateTime(char *buffer, time_t *time)
{
    if (buffer == NULL) {
        return;
    }
    strftime(buffer, 20, "%Y-%m-%d_%H-%M-%S", localtime(time));
}

bool getParamsFromArgs(
    int argc, char const *argv[],
    int *nMin, int *nMax, int *nStep,
    int *elemMinValue, int *elemMaxValue)
{
    int min = 0;
    int max = 0;
    int step = 0;
    int minVal = 0;
    int maxVal = 0;
    bool fail = 0;

    if (argc != 6) {
        return false;
    }

    fail |= (sscanf(argv[1], "%d", &min) != 1);
    fail |= (sscanf(argv[2], "%d", &max) != 1);
    fail |= (sscanf(argv[3], "%d", &step) != 1);
    fail |= (sscanf(argv[4], "%d", &minVal) != 1);
    fail |= (sscanf(argv[5], "%d", &maxVal) != 1);

    if(fail) {
        return false;
    }

    *nMin = min;
    *nMax = max;
    *nStep = step;
    *elemMinValue = minVal;
    *elemMaxValue = maxVal;
    return true;
}

bool getParamsFromTerminal(
    int *nMin, int *nMax, int *nStep,
    int *elemMinValue, int *elemMaxValue)
{
    const int lineSize = 12;
    char line [lineSize];
    int min = 0;
    int max = 0;
    int step = 0;
    int minVal = 0;
    int maxVal = 0;
    bool fail = 0;

    fputs("Entre o tamanho mínimo dos arrays: ", stdout);
    fgets(line, lineSize, stdin);
    fail |= (sscanf(line, "%d", &min) != 1);
    fputs("\n", stdout);

    fputs("Entre o tamanho máximo dos arrays: ", stdout);
    fgets(line, lineSize, stdin);
    fail |= (sscanf(line, "%d", &max) != 1);
    fputs("\n", stdout);

    fputs("Entre o tamanho do passo: ", stdout);
    fgets(line, lineSize, stdin);
    fail |= (sscanf(line, "%d", &step) != 1);
    fputs("\n", stdout);

    fputs("Entre o valor mínimo dos elementos: ", stdout);
    fgets(line, lineSize, stdin);
    fail |= (sscanf(line, "%d", &minVal) != 1);
    fputs("\n", stdout);

    fputs("Entre o valor máximo dos elementos: ", stdout);
    fgets(line, lineSize, stdin);
    fail |= (sscanf(line, "%d", &maxVal) != 1);
    fputs("\n", stdout);

    if (fail != false ) {
        puts("Não será possivel criar os arrys com os argumentos fornecidos.");
        puts("Ignorando valores fornecidos.");
        fputs("\n", stdout);
        return false;
    }

    *nMin = min;
    *nMax = max;
    *nStep = step;
    *elemMinValue = minVal;
    *elemMaxValue = maxVal;
    return true;
}