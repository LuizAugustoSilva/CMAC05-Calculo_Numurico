#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
    return pow(x, 3) * exp(x);
}

double f4(double x)
{
    return exp(x)*pow(x, 3) + 12*exp(x)*pow(x, 2) + 36*exp(x)*x + 24*exp(x);
}

int main()
{
    int i, n;
    double a, b, h, result, erro, maior;
    double *x, *y, *derivada4;

    printf("Intervalo de integracao [a, b]:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);

    printf("Quantos subintervalos (numero par): ");
    scanf("%d", &n);

    if(n%2)
        n++;
    
    h = (b-a)/n;
    x = (double *)malloc((n+1) * sizeof(double));
    y = (double *)malloc((n+1) * sizeof(double));
    derivada4 = (double *)malloc((n+1) * sizeof(double));

    printf("\n");
    for(i = 0; i <= n; i++)
    {
        x[i] = a + h*i;
        y[i] = f(x[i]);
        derivada4[i] = f4(x[i]);

        printf("x: %.4lf, y: %.4lf, dx4: %.4lf\n", x[i], y[i], derivada4[i]);
    }

    result = y[0] + y[n];
    maior = derivada4[0];
    for(i = 1; i < n; i++)
    {
        if(i%2 == 0)
            result += 2*y[i];
        else
            result += 4*y[i];
        
        if(derivada4[i] > maior)
            maior = derivada4[i];
    }
    if(derivada4[n] > maior)
        maior = derivada4[n];

    result = result * h/3;
    erro = pow(h, 4)/180 * (b-a) * maior;
    
    printf("\nValor aproximado da integral: %.7lf\n", result);
    printf("Erro: %.7lf\n", erro);

    free(x);
    free(y);
    free(derivada4);

    return 0;
}