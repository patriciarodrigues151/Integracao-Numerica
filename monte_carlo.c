#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>


double* geradorPontosAleatorios(double a, double b, int n) {
    srand(time(NULL));
    
    double* pontos = (double*)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        pontos[i] = (((double)rand() / RAND_MAX) * (b - a)) + a;
    }
    
    pontos[0] = a;
    pontos[n-1] = b;
    
    return pontos;
}

double* calculaSenos(double pontos[], int n){
    double* senos = (double*)malloc(n * sizeof(double));

    for(int i = 0; i < n; i++){
        senos[i] = sin(pontos[i]);
    }
    
    return senos;
}

double G(int i, double x) {
    switch (i) {
        case 1:
            return sin(x);
        case 2:
            return pow(x, 3);
        case 3:
            return exp(-x);
        default:
            return 0.0;  // Valor padrão caso i não corresponda a nenhum caso
    }
}

double integracaoDeMonteCarlo(double a, double b, int n, int func) {
    double* pontos = geradorPontosAleatorios(a, b, n);
    double somaGs = 0;

    for (int i = 0; i < n; i++) {
        somaGs += G(func, pontos[i]);
    }

    double I = ((b - a)/n) * somaGs;

    free(pontos);
    return I;
}

double aproximaPi(int n) {
    int pontosDentroCirculo = 0;

    for (int i = 0; i < n; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1) {
            pontosDentroCirculo++;
        }
    }

    double piAproximado = 4.0 * pontosDentroCirculo / n;

    return piAproximado;
}


int main() {
    int opcao;
    printf("Escolha uma opção:\n1 - ∫ [0,1] sin(x) dx\n2 - ∫ [3,7] x^3 dx\n3 - ∫ [0,∞] e^(-x) dx\n4 - Aproximar o valor de π\n");
    scanf("%d", &opcao);

    int n;
    
    printf("Quantos pontos gostaria de gerar?\nDigite n: ");
    scanf("%d", &n);

    double resultado = 0.0;

    switch (opcao) {
        case 1:
            resultado = integracaoDeMonteCarlo(0, 1, n, 1);
            break;
        case 2:
            resultado = integracaoDeMonteCarlo(3, 7, n, 2);
            break;
        case 3:
            resultado = integracaoDeMonteCarlo(0, log(DBL_MAX) / log(M_E), n, 3);
            break;
        case 4:
            resultado = aproximaPi(n);
            break;
        default:
            printf("Opção inválida!\n");
            return 0;
    }

    printf("O resultado da integração é: %.6lf\n", resultado);

    return 0;
}
