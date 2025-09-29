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

int main()
{
    int i, j, k, N, ok, tamanho;
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
        primeiro = (double *)malloc(2 * sizeof(double));
        segundo = (double *)malloc(2 * sizeof(double));
        tamanho = 2;
        denominador = 1;
        ok = 0;
        for(j = 0; j < N; j++)
        {
            if(j == i)
                continue;

            denominador *= pontosX[i] - pontosX[j];

            if(!ok)
            {
                primeiro[0] = 1;
                primeiro[1] = -pontosX[j];
                ok = 1;
            }
            else
            {
                segundo[0] = 1;
                segundo[1] = -pontosX[j];
                primeiro = multTerms(primeiro, &tamanho, segundo, 2);
            }
        }

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
        printf("%lf ", resp[i]);
    }
    printf("\n");

    free(primeiro);
    free(pontosX);
    free(pontosY);
    free(resp);
    for(i = 0; i < N; i++)
        free(L[i]);
    free(L);

    return 0;
}
