#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calcularErro(double *resultsTemp, double *estimativa, int N);
void printPasso(double *resultsTemp, double *estimativa, int N);
void printLinha(int i, double **matriz, double *termos, double *resultsTemp, int N);
void trocarLinhas(double **matriz, double *termos, int N);

int main()
{
    int N, i, j, k = 0;
    double erro = 100.0, precisao;
    double **matriz, *termos, *resultsTemp, *estimativa, soma;

    printf("Presisao: ");
    scanf("%lf", &precisao);
    printf("Tamanho da matriz (NxN): ");
    scanf("%d", &N);

    matriz = (double **)malloc(N * sizeof(double *));
    termos = (double *)malloc(N * sizeof(double));
    resultsTemp = (double *)malloc(N * sizeof(double));
    estimativa = (double *)malloc(N * sizeof(double));
    for(i = 0; i < N; i++)
    {
        matriz[i] = (double *)malloc(N * sizeof(double));
        resultsTemp[i] = 1;
        estimativa[i] = 1;
    }

    printf("Equacoes linha a linha:\n");
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            scanf("%lf", &matriz[i][j]);
        scanf("%lf", &termos[i]);
    }
    printf("\n");

    //trocarLinhas(matriz, termos, N);

    while(erro > precisao)
    {
        k++;
        printf("Passo %d\n", k);
        for(i = 0; i < N; i++)
        {
            soma = termos[i];
            for(j = 0; j < N; j++)
            {
                if(j != i)
                {
                    soma += (-matriz[i][j]) * resultsTemp[j];
                }
            }
            printLinha(i, matriz, termos, resultsTemp, N);
            resultsTemp[i] = soma/matriz[i][i];
        }
        printPasso(resultsTemp, estimativa, N);
        erro = calcularErro(resultsTemp, estimativa, N);
    }

    for(i = 0; i < N; i++)
    {
        printf("x%d: %lf\n", i+1, resultsTemp[i]);
    }
    printf("Erro: %lf\n", erro);

    for(i = 0; i < N; i++)
        free(matriz[i]);
    free(matriz);
    free(termos);
    free(resultsTemp);
    free(estimativa);

    return 0;
}


double calcularErro(double *resultsTemp, double *estimativa, int N)
{
    int maiorIdx = 0, i;
    double erro, resp;

    erro = fabs(resultsTemp[0] - estimativa[0]);
    for(i = 0; i < N; i++)
    {
        if(fabs(resultsTemp[i]) > fabs(resultsTemp[maiorIdx]))
            maiorIdx = i;

        if(fabs(resultsTemp[i] - estimativa[i]) > erro)
            erro = fabs(resultsTemp[i] - estimativa[i]);

        estimativa[i] = resultsTemp[i];
    }
    resp = erro/fabs(resultsTemp[maiorIdx]);
    printf("Δr = %.2lf/%.2lf = %.4lf\n\n", erro, fabs(resultsTemp[maiorIdx]), resp);

    return resp;
}

void printPasso(double *resultsTemp, double *estimativa, int N)
{
    int i;

    for(i = 0; i < N; i++)
        printf("x%d = %.2lf\tΔx%d = %.2lf\n", i+1, resultsTemp[i], i+1, fabs(resultsTemp[i] - estimativa[i]));
}

void printLinha(int i, double **matriz, double *termos, double *resultsTemp, int N)
{
    int j;

    printf("x%d = (%.2lf", i+1, termos[i]);
    for(j = 0; j < N; j++)
    {
        if(j != i)
        {
            if(matriz[i][j] <= 0)
                printf(" + %.2lf", fabs(matriz[i][j]));
            else
                printf(" - %.2lf", matriz[i][j]);

            if(resultsTemp[j] < 0)
                printf("*(%.2lf)", resultsTemp[j]);
            else
                printf("*%.2lf", resultsTemp[j]);
        }
    }
    printf(")/%.2lf\n", matriz[i][i]);
}

void trocarLinhas(double **matriz, double *termos, int N)
{
    int i, j, k, maxRow;
    double tmp, *tmpRow;

    for(i = 0; i < N; i++)
    {
        maxRow = i;
        for(k = i+1; k < N; k++)
        {
            if(fabs(matriz[k][i]) > fabs(matriz[maxRow][i]))
                maxRow = k;
        }

        if(maxRow != i)
        {
            tmpRow = matriz[i];
            matriz[i] = matriz[maxRow];
            matriz[maxRow] = tmpRow;

            tmp = termos[i];
            termos[i] = termos[maxRow];
            termos[maxRow] = tmp;
        }
    }
}