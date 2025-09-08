#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void imprimirMatriz(int k, int N, double **matriz, double M)
{
    int i, j;

    printf("\nPasso %d:\n", k);
    printf("M: %lf\n", M);
    for(i=0; i<N; i++)
    {
        for(j=0; j<N+1; j++)
        {
            printf("%.2lf / ", matriz[i][j]);
        }
        printf("\n");
    }
}

void trocaLinhas(double **matriz, int linha1, int linha2, int N)
{
    double temp;
    for(int j = 0; j < N+1; j++)
    {
        temp = matriz[linha1][j];
        matriz[linha1][j] = matriz[linha2][j];
        matriz[linha2][j] = temp;
    }
}

int main()
{
    int i, j, k, N, cont;
    double **matriz, **matrizOriginal, *linhaSuporte, *resultado, M;

    printf("Qual o tamanho da matriz? (NxN): ");
    scanf("%d", &N);

    matriz = (double **)malloc(N * sizeof(double *));
    matrizOriginal = (double **)malloc(N * sizeof(double *));
    for(i=0; i<N; i++)
    {
        matriz[i] = (double *)malloc((N+1) * sizeof(double));
        matrizOriginal[i] = (double *)malloc((N+1) * sizeof(double));
    }

    printf("Insira os valores, linha por linha:\n");
    for(i=0; i<N; i++)
    {
        for(j=0; j<N+1; j++)
        {
            scanf("%lf", &matriz[i][j]);
            matrizOriginal[i][j] = matriz[i][j];
        }
    }

    cont = 0;
    for(k=0; k<N-1; k++)
    {
        // --- Pivotação Parcial ---
        int maxLinha = k;
        for(i=k+1; i<N; i++)
        {
            if(fabs(matriz[i][k]) > fabs(matriz[maxLinha][k]))
                maxLinha = i;
        }
        if(maxLinha != k)
        {
            trocaLinhas(matriz, k, maxLinha, N);
            printf("\nTrocando linhas %d e %d\n", k+1, maxLinha+1);
        }

        // --- Eliminação ---
        for (i = k+1; i < N; i++)
        {
            M = matriz[i][k] / matriz[k][k];
            linhaSuporte = calculaLinha(N+1, M, matriz[k]);

            for (j = 0; j < N+1; j++)
            {
                matriz[i][j] -= linhaSuporte[j];
            }
            imprimirMatriz(cont, N, matriz, M);
            cont++;

            free(linhaSuporte); // liberando a linha calculada a cada iteração
        }
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

    printf("\nVerificacao:\n");
    for(i=0; i<N; i++)
    {
        for(j=0; j<N+1; j++)
        {
            if(j == N)
                printf(" = %.2lf\n", matrizOriginal[i][j]);
            else if(matrizOriginal[i][j] < 0)
                printf(" %.2lf * %.2lf", matrizOriginal[i][j], resultado[j]);
            else
                printf(" + %.2lf * %.2lf", matrizOriginal[i][j], resultado[j]);
        }
        printf("\n");
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
        free(matrizOriginal[i]);
    }
    free(matriz);
    free(matrizOriginal);
    free(resultado);

    return 0;
}
