/*
    Name: Lab#2
    Author: Prof. Joao Costa / Modificado para alínea d
    Description: Paralelização de loop interno com dependências — versão sem cópia do vetor V em cada iteração
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOTALSIZE 1000
#define NUMITER 200

// Função dummy
#define f(x,y) ((x + y) / 2.0)

int main(int argc, char *argv[]) {
    int i, iter;

    // Vetores
    double *V = (double *) malloc(TOTALSIZE * sizeof(double));
    double *Vtmp = (double *) malloc(TOTALSIZE * sizeof(double));

    // Inicialização do vetor V
    for (i = 0; i < TOTALSIZE; i++) {
        V[i] = 100.0 + i;
    }

    // Ponteiros auxiliares
    double *in = V;
    double *out = Vtmp;
    double *swap;

    // Iterações
    for (iter = 0; iter < NUMITER; iter++) {
        #pragma omp parallel for
        for (i = 0; i < TOTALSIZE - 1; i++) {
            out[i] = f(in[i], in[i + 1]);
        }

        // Preserva o último valor
        out[TOTALSIZE - 1] = in[TOTALSIZE - 1];

        // Troca os vetores
        swap = in;
        in = out;
        out = swap;
    }

    // Impressão do resultado final (que estará em 'in')
    printf("Output:\n");
    for (i = 0; i < TOTALSIZE; i++) {
        printf("%4d %f\n", i, in[i]);
    }

    // Liberação da memória
    free(V);
    free(Vtmp);

    return 0;
}
