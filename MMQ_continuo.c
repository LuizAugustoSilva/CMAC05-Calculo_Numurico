#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NPTS 1000

double f(double x)
{
    return exp(x);
}

void eliminacao_gauss(double **A, double *b, int n)
{
    int i, j, k, max;
    double tmp, fator, soma;
    double *x = (double *)malloc(n * sizeof(double));

    // Eliminação progressiva com pivoteamento parcial
    for (i = 0; i < n - 1; i++)
    {
        max = i;
        for (k = i + 1; k < n; k++)
            if (fabs(A[k][i]) > fabs(A[max][i]))
                max = k;

        if (max != i)
        {
            for (j = 0; j < n; j++)
            {
                tmp = A[i][j];
                A[i][j] = A[max][j];
                A[max][j] = tmp;
            }
            tmp = b[i];
            b[i] = b[max];
            b[max] = tmp;
        }

        for (k = i + 1; k < n; k++)
        {
            fator = A[k][i] / A[i][i];
            for (j = i; j < n; j++)
                A[k][j] -= fator * A[i][j];
            b[k] -= fator * b[i];
        }
    }

    // Substituição regressiva
    for (i = n - 1; i >= 0; i--)
    {
        soma = 0.0;
        for (j = i + 1; j < n; j++)
            soma += A[i][j] * x[j];
        x[i] = (b[i] - soma) / A[i][i];
    }

    printf("\nCoeficientes (a[i]):\n");
    for (i = 0; i < n; i++)
        printf("a[%d] = %lf\n", i, x[i]);

    free(x);
}

int main()
{
    int i, j, grau;
    double a, b, h, x;
    double **alfa, *beta;

    printf("Intervalo de integracao [a, b]:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);

    printf("Grau do polinomio de ajuste: ");
    scanf("%d", &grau);
    grau++;

    alfa = (double **)malloc(grau * sizeof(double *));
    for (i = 0; i < grau; i++)
        alfa[i] = (double *)calloc(grau, sizeof(double));
    beta = (double *)calloc(grau, sizeof(double));

    h = (b - a) / (NPTS - 1);

    // Integração numérica (regra dos trapézios)
    for (i = 0; i < NPTS; i++)
    {
        x = a + i * h;
        double peso = (i == 0 || i == NPTS - 1) ? 0.5 : 1.0;
        double y = f(x);

        for (j = 0; j < grau; j++)
        {
            beta[j] += peso * y * pow(x, j);
            for (int k = 0; k < grau; k++)
                alfa[j][k] += peso * pow(x, j + k);
        }
    }

    // Multiplica tudo por h (fator da regra dos trapézios)
    for (i = 0; i < grau; i++)
    {
        beta[i] *= h;
        for (j = 0; j < grau; j++)
            alfa[i][j] *= h;
    }

    eliminacao_gauss(alfa, beta, grau);

    for (i = 0; i < grau; i++)
        free(alfa[i]);
    free(alfa);
    free(beta);

    return 0;
}
