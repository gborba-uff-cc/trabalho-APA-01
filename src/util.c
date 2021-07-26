#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/resource.h>

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
