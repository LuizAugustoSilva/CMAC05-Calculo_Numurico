#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double calcularErro(double *resultsTemp, double *estimativa, int N)
{
    int maiorIdx = 0, i;
    double erro;

    erro = fabs(resultsTemp[0] - estimativa[0]);
    for(i = 0; i < N; i++)
    {
        if(fabs(resultsTemp[i]) > fabs(resultsTemp[maiorIdx]))
            maiorIdx = i;

        if(fabs(resultsTemp[i] - estimativa[i]) > erro)
            erro = fabs(resultsTemp[i] - estimativa[i]);

        estimativa[i] = resultsTemp[i];
    }
    
    return erro/fabs(resultsTemp[maiorIdx]);
}

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
        estimativa[i] = 1;
    }

    printf("Equacoes linha a linha:\n");
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            scanf("%lf", &matriz[i][j]);
        scanf("%lf", &termos[i]);
    }

    //trocarLinhas(matriz, termos, N);

    while(erro > precisao)
    {
        for(i = 0; i < N; i++)
        {
            soma = termos[i];
            for(j = 0; j < N; j++)
            {
                if(j != i)
                {
                    soma += (-matriz[i][j]) * estimativa[j];
                }
            }
            resultsTemp[i] = soma/matriz[i][i];
        }
        erro = calcularErro(resultsTemp, estimativa, N);
        k++;
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