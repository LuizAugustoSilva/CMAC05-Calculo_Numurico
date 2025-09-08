#include <stdio.h>
#include <stdlib.h>

double * calculaLinha(int tamanho, double M, double *linha)
{
    int i;
    double *linhaCalculada = (double *)malloc(tamanho * sizeof(double));

    for(i=0; i<tamanho; i++)
    {
        linhaCalculada[i] = linha[i] * M;
    }

    return linhaCalculada;
}

int main()
{
    int i, j, k, N;
    double **matriz, *linhaSuporte, *resultado, M;

    printf("Qual o tamanho da matriz? (NxN): ");
    scanf("%d", &N);

    matriz = (double **)malloc(N * sizeof(double *));
    for(i=0; i<N; i++)
    {
        matriz[i] = (double *)malloc((N+1) * sizeof(double));
    }

    printf("Insira os valores, linha por linha:\n");
    for(i=0; i<N; i++)
    {
        for(j=0; j<N+1; j++)
        {
            scanf("%lf", &matriz[i][j]);
        }
    }

    for(k=0; k<N-1; k++)
    {
        for (i = k+1; i < N; i++)
        {
            M = matriz[i][k] / matriz[k][k];
            linhaSuporte = calculaLinha(N+1, M, matriz[k]);

            for (j = 0; j < N+1; j++)
            {
                matriz[i][j] = matriz[i][j] - linhaSuporte[j];
            }
        }
    }

    for(i=0; i<N; i++)
    {
        for(j=0; j<N+1; j++)
        {
            printf("%.2lf / ", matriz[i][j]);
        }
        printf("\n");
    }

    resultado = (double *)malloc(N * sizeof(double));
    for(i = N-1; i >= 0; i--)
    {
        resultado[i] = matriz[i][N];
        for(j = i+1; j < N; j++)
        {
            resultado[i] -= matriz[i][j] * resultado[j];
        }
        resultado[i] /= matriz[i][i];
    }

    printf("\nSolucoes do sistema:\n");
    for(i=0; i<N; i++)
    {
        printf("x%d = %.4lf\n", i+1, resultado[i]);
    }

    //Desalocando
    for(i=0; i<N; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    free(linhaSuporte);
    free(resultado);

    return 0;
}