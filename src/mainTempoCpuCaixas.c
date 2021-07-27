#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#include "ordenacaoMetodoCaixas.h"
#include "tests.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    int elemMinValue = 0;
    int elemMaxValue = 1000;
    int arraySizeStep = 100;
    int arraySizeMinimum = 1000;
    int arraySizeMaximum = 25000;
    const int arraySeeds[] = {2000, 566, 30610, 134, 2001};
    const int nArraySeeds = sizeof(arraySeeds)/sizeof(int);
    const int repetitionsPerArray = 1; // deve ser maior que 0

    int *array = NULL;
    int arraySize = 0;
    int arraySeed = 0;
    int maxValue = 0;
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

    // interage com o usuário --------------------------------------------------
    bool paramsAreValids = true;
    // tenta pegar parametros via argumentos do programa
    if (getParamsFromArgs(argc, argv, &arraySizeMinimum, &arraySizeMaximum,
        &arraySizeStep, &elemMinValue, &elemMaxValue)) {
    }
    // tenta pegar parametros do terminal, se não consegui via argumentos
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

    // Afere tempo de execução -------------------------------------------------
    // cria o arquivo de saída com as médias
    FILE *fp = NULL;
    char outputFilename[100];
    time_t startTime = time(NULL);
    char todayDate[20];
    getStrDateTime(todayDate, &startTime);
    sprintf(outputFilename, "./results/meansCaixas-%s.dat", todayDate);
    fp = fopen(outputFilename, "a");

    // para cada um dos tamanhos de array
    for (arraySize = arraySizeMinimum; arraySize <= arraySizeMaximum; arraySize += arraySizeStep) {
        maxValue = arraySize;
        dt_cpu_acc = 0.0;
        dt_kernel_acc = 0.0;
        // para cada tamanho de array, gera um array usando uma das seeds
        for (b = 0; b < nArraySeeds; b++) {
            arraySeed = arraySeeds[b];
            // realiza x repetições para cada par de tamanho e seed do array
            for (c = 0; c < repetitionsPerArray; c++) {
                array = generateRandomIntArray(
                    array, arraySize, elemMinValue, maxValue, arraySeed);
                if (array == NULL) {
                    printf("Abortando programa...\nNão foi possível gerar o array de tamanho %d com a seed %d.\n",
                        arraySize, arraySeed);
                    exit(1);
                }

                // // apresenta array antes de ordenar
                // printIntArray(array,arraySize);

                // toma o tempo de cpu e de kernel
                Tempo_CPU_Sistema(&t_cpu_start, &t_kernel_start);
                ordenacaoMetodoCaixas(array, arraySize, elemMinValue, maxValue);
                Tempo_CPU_Sistema(&t_cpu_finish, &t_kernel_finish);

                // // apresenta array depois de ordenado
                // printIntArray(array,arraySize);

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
        printf("Método das caixas para o array de tamanho: %d. (%d arrays ordenados)\n    Tempo médio CPU: %lfs\n    Tempo médio kernel: %lfs\n",
            arraySize, nArraySeeds * repetitionsPerArray, 
            dt_cpu_meanPerSize, dt_kernel_meanPerSize);
        printf("\n");

        // armazena médias no arquivo
        if (fp != NULL) {
            // armazena um par "arraySize dt_cpu_meanPerSize" em cada linha do arquivo
            fprintf(fp,"%d\t%lf\n", arraySize, dt_cpu_meanPerSize);
            fflush(fp);
        }
    }

    if (fp != NULL) {
        fclose(fp);
    }
    return 0;
}