#include <stdio.h>
#include <stdlib.h>

#include "ordenacaoMetodoCaixas.h"
#include "tests.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    // executa teste -----------------------------------------------------------
    bool testSucceeded = testOrdenacaoMetodoCaixas();
    printf(
        testSucceeded 
        ? "Teste da ordenacao pelo método caixas: Sucesso\n" 
        : "Teste da ordenacao pelo método caixas: Falhou\n");
    printf("\n");

    if (testSucceeded == false) {
        printf("Abortando programa...\nO algoritmo não passou no teste de ordenação.\n");
        return 1;
    }

    // -------------------------------------------------------------------------
    const int elemMinValue = 0;
    const int elemMaxValue = 1000;
    const int arraySizes[] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
    const int nArraySizes = sizeof(arraySizes)/sizeof(int);
    const int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    const int nArraySeeds = sizeof(arraySeeds)/sizeof(int);
    const int repetitionsPerArray = 1000; // deve ser maior que 0

    int *array = NULL;
    int arraySize = 0;
    int arraySeed = 0;
    int a = 0;
    int b = 0;
    int c = 0;

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

                // toma o tempo de cpu e de kernel
                Tempo_CPU_Sistema(&t_cpu_start, &t_kernel_start);
                ordenacaoMetodoCaixas(array, arraySize, elemMinValue, elemMaxValue);
                Tempo_CPU_Sistema(&t_cpu_finish, &t_kernel_finish);

                // computa o tempo de cpu
                dt_cpu = t_cpu_finish - t_cpu_start;
                dt_cpu_acc += dt_cpu;
                dt_kernel = t_kernel_finish - t_kernel_start;
                dt_kernel_acc += dt_kernel;

                // // apresenta tempos parciais
                // printf("Método das caixas para o array de tamanho: %d, gerado com a seed: %d.\n    Tempo CPU: %f\n    Tempo kernel: %f\n",
                //     arraySize, arraySeed, dt_cpu, dt_kernel);
                // printf("\n");
            }
        }
        // computa as médias para cada tamanho de array
        dt_cpu_meanPerSize = dt_cpu_acc / (nArraySeeds * repetitionsPerArray);
        dt_kernel_meanPerSize = dt_kernel_acc / (nArraySeeds * repetitionsPerArray);

        // apresenta tempos médios
        printf("Método das caixas para o array de tamanho: %d. (%d arrays ordenados)\n    Tempo médio total CPU: %fs\n    Tempo médio total kernel: %fs\n",
            arraySize, nArraySeeds * repetitionsPerArray, 
            dt_cpu_meanPerSize, dt_kernel_meanPerSize);
        printf("\n");
    }
    return 0;
}