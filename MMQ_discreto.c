#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void eliminacao_gauss(double **A, double *b, int n)
{
    int i, j, k, max;
    double tmp, fator, soma;
    double *x = (double *)malloc(n * sizeof(double));

    // Eliminação progressiva (com pivoteamento parcial)
    for (i = 0; i < n - 1; i++)
    {
        // Pivoteamento parcial
        max = i;
        for (k = i + 1; k < n; k++)
            if (fabs(A[k][i]) > fabs(A[max][i]))
                max = k;

        // Troca de linhas (A e b)
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

        // Eliminação
        for (k = i + 1; k < n; k++)
        {
            if (A[i][i] == 0)
            {
                printf("Erro: pivô nulo!\n");
                free(x);
                return;
            }
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
        printf("a[%d] = %lf\n", i + 1, x[i]);

    free(x);
}

int main()
{
    int i, j, k, N, M;
    double *x, *y, *beta;
    double **alfa, **g;

    printf("Qual grau da funcao do resultado?: ");
    scanf("%d", &N);
    N++;
    printf("Quantos pontos dados?: ");
    scanf("%d", &M);

    x = (double *)malloc(M * sizeof(double));
    y = (double *)malloc(M * sizeof(double));
    g = (double **)malloc(N * sizeof(double *));
    beta = (double *)malloc(N * sizeof(double));
    alfa = (double **)malloc(N * sizeof(double *));

    for(i = 0; i < N; i++)
    {
        alfa[i] = (double *)malloc(N * sizeof(double));
        g[i] = (double *)malloc(M * sizeof(double));
    }

    for (i = 0; i < N; i++)
    {
        beta[i] = 0;
        for (j = 0; j < N; j++)
            alfa[i][j] = 0;
    }

    for(i = 0; i < M; i++)
    {
        printf("x%d: ", i);
        scanf("%lf", &x[i]);
        printf("f(x%d): ", i);
        scanf("%lf", &y[i]);
    }

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            g[i][j] = pow(x[j], N - i - 1);
            beta[i] += y[j] * g[i][j];
        }
    }

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            for(k = 0; k < M; k++)
            {
                alfa[i][j] += g[i][k] * g[j][k];
            }
        }
    }

    eliminacao_gauss(alfa, beta, N);

    for (i = 0; i < N; i++)
    {
        free(alfa[i]);
        free(g[i]);
    }
    free(alfa);
    free(g);
    free(x);
    free(y);
    free(beta);

    return 0;
}
