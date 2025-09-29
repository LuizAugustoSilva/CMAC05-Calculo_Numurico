#include <stdio.h>
#include <stdlib.h>

double *multTerms(double *t1, int *tam1, double *t2, int tam2)
{
    int i, j;
    double *result;

    result = (double *)calloc((*tam1 + tam2 - 1), sizeof(double));

    for(i = 0; i < *tam1; i++)
    {
        for(j = 0; j < tam2; j++)
        {
            result[i+j] += t1[i] * t2[j];
        }
    }
    *tam1 = (*tam1 + tam2 - 1);
    free(t1);

    return result;
}

void printEquacao(int i, double *equacao, int tam, double denominador)
{
    int j;

    printf("\nL%d(x) = (%.4lfx^%d", i, equacao[0], tam-1);
    for(j = 1; j < tam-2; j++)
    {
        if(equacao[j] < 0)
            printf(" %.4lfx^%d", equacao[j], tam-1-j);
        else
            printf(" +%.4lfx^%d", equacao[j], tam-1-j);
    }
    if(equacao[j] < 0)
        printf(" %.4lfx", equacao[j]);
    else
        printf(" +%.4lfx", equacao[j]);

    j++;
    if(equacao[j] < 0)
        printf(" %.4lf", equacao[j]);
    else
        printf(" +%.4lf", equacao[j]);

    printf(")/%.4lf\n", denominador);
}

int main()
{
    int i, j, N, tamanho;
    double denominador;
    double *pontosX, *pontosY, *resp, *primeiro, *segundo;
    double **L;
    
    printf("Informe a quantidade de pontos: ");
    scanf("%d", &N);

    pontosX = (double *)malloc(N * sizeof(double));
    pontosY = (double *)malloc(N * sizeof(double));
    resp = (double *)calloc(N, sizeof(double));
    L = (double **)malloc(N * sizeof(double *));

    printf("Informe os pontos xi e f(xi):\n");
    for(i = 0; i < N; i++)
        scanf("%lf %lf", &pontosX[i], &pontosY[i]);

    for(i = 0; i < N; i++)
    {
        primeiro = (double *)malloc(sizeof(double));
        segundo = (double *)malloc(2 * sizeof(double));
        primeiro[0] = 1;
        tamanho = 1;
        denominador = 1;
        for(j = 0; j < N; j++)
        {
            if(j == i)
                continue;

            denominador *= pontosX[i] - pontosX[j];

            segundo[0] = 1;
            segundo[1] = -pontosX[j];
            primeiro = multTerms(primeiro, &tamanho, segundo, 2);
        }

        printEquacao(i, primeiro, N, denominador);

        for(j = 0; j < N; j++)
            primeiro[j] = pontosY[i] / denominador * primeiro[j];
        L[i] = primeiro;
        
        free(segundo);
    }

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            resp[i] += L[j][i];
        }
    }

    printf("\ng(x) = ");
    printf("%.4lfx^%d ", resp[0], N-1);
    for(i = 1; i < N-2; i++)
    {
        if(resp[i] < 0)
            printf("%.4lfx^%d ", resp[i], N-1-i);
        else
            printf("+%.4lfx^%d ", resp[i], N-1-i);
    }
    if(resp[i] < 0)
        printf("%.4lfx ", resp[i]);
    else
        printf("+%.4lfx ", resp[i]);
    
    i++;
    if(resp[i] < 0)
        printf("%.4lf\n", resp[i]);
    else
        printf("+%.4lf\n", resp[i]);

    free(primeiro);
    free(pontosX);
    free(pontosY);
    free(resp);
    for(i = 0; i < N; i++)
        free(L[i]);
    free(L);

    return 0;
}
