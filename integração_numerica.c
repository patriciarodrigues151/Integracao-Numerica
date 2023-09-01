#include <stdio.h>
#include <stdlib.h>

// Calcula os Li(X)s de Lagrange
double calculaLi(double x, double xA[], int i, int n) {
    double numerador = 1;
    double denominador = 1;

    for (int k = 0; k < n; k++) {
        if (i != k) {
            numerador *= x - xA[k];
            denominador *= xA[i] - xA[k];
        }
    }
    return numerador / denominador;
}

// Calcula os Pn(X)s de Lagrange
double Pn_Lagrange(double fx[], double xA[], int n, double x) {
    double resultado = 0;

    for (int i = 0; i < n; i++) {
        resultado += fx[i] * calculaLi(x, xA, i, n);
    }

    return resultado;
}

// Regra do Trapézio
double* regraDoTrapezio(double x[], double fx[], int n) {
    // a, b são os pontos extremos
    double a = x[0];
    double b = x[n - 1];

    // h é o tamanho de cada n-1 subintervalos (equidistantes)
    double h = (b - a) / n;

    double* area = (double*)malloc((n - 1) * sizeof(double));
    // calcula a área de cada subintervalo
    for (int i = 0; i < n - 1; i++) {
        area[i] = (h / 2) * (fx[i] + fx[i + 1]);
    }

    return area;
}

// Regra de Simpson
double* regraDeSimpson(double x[], double fx[], int n) {
    // a, b são os pontos extremos
    double a = x[0];
    double b = x[n - 1];

    // h é o tamanho de cada n-1 subintervalos (equidistantes)
    double h = (b - a) / n;

    double* area = (double*)malloc((n - 1) * sizeof(double));
    // calcula a área de cada par de subintervalos usando a regra de Simpson
    for (int k = 1; k < (n-1)/2; k++) {
        area[k] = (h / 3) * (fx[2*k-2] + 4 * fx[2*k - 1] + fx[2*k]);
    }

    return area;
}

int main() {
    double fx[] = {0.0000, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537};
    double x[] = {0, 5, 10, 15, 20, 25, 30};
    int n = sizeof(x) / sizeof(x[0]);

    for (int i = 0; i < n; i++) {
        double resultado = Pn_Lagrange(fx, x, n, x[i]);
        printf("Pn(%g) = %g\n", x[i], resultado);
    }

    double* areaTrapezio = regraDoTrapezio(x, fx, n);
    printf("Área do gráfico usando Trapézio:\n");
    double somaTrapezio = 0;
    for (int i = 0; i < n - 1; i++) {
        printf("Subintervalo %d: %g\n", i + 1, areaTrapezio[i]);
        somaTrapezio += areaTrapezio[i];
    }
    free(areaTrapezio);

    double* areaSimpson = regraDeSimpson(x, fx, n);
    printf("Área do gráfico usando Simpson:\n");
    double somaSimpson = 0;
    for (int i = 0; i < n - 1; i += 2) {
        printf("Subintervalo %d: %g\n", i + 1, areaSimpson[i]);
        somaSimpson += areaSimpson[i];
    }
    free(areaSimpson);

    printf("Soma total das áreas:\n");
    printf("Trapézio: %g\n", somaTrapezio);
    printf("Simpson: %g\n", somaSimpson);

    return 0;
}
