#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
    return pow(x, 3) * exp(x);
}

double f2(double x)
{
    return exp(x)*pow(x, 3) + 6*exp(x)*pow(x, 2) + 6*exp(x)*x;
}

int main()
{
    int i, n;
    double a, b, h, result, erro, maior;
    double *x, *y, *derivada2;

    printf("Intervalo de integracao [a, b]:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);

    printf("Quantos subintervalos: ");
    scanf("%d", &n);
    
    h = (b-a)/n;
    x = (double *)malloc((n+1) * sizeof(double));
    y = (double *)malloc((n+1) * sizeof(double));
    derivada2 = (double *)malloc((n+1) * sizeof(double));

    printf("\n");
    for(i = 0; i <= n; i++)
    {
        x[i] = a + h*i;
        y[i] = f(x[i]);
        derivada2[i] = f2(x[i]);

        printf("x: %.4lf, y: %.4lf, dx2: %.4lf\n", x[i], y[i], derivada2[i]);
    }

    result = y[0] + y[n];
    maior = derivada2[0];
    for(i = 1; i < n; i++)
    {
        result += 2*y[i];
        
        if(derivada2[i] > maior)
            maior = derivada2[i];
    }
    if(derivada2[n] > maior)
        maior = derivada2[n];

    result = result * h/2;
    erro = pow(h, 2)/12 * (b-a) * maior;
    
    printf("\nValor aproximado da integral: %.7lf\n", result);
    printf("Erro: %.7lf\n", erro);

    free(x);
    free(y);
    free(derivada2);

    return 0;
}
