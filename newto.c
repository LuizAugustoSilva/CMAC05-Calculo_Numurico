#include <stdio.h>
#include <math.h>

double function(double x)
{
    return cos(x) - x*x;
}

double derivada(double x)
{
    return -sin(x) - 2*x;
}

int main()
{
    int k;
    double x, y, precisao;

    printf("Inicio: ");
    scanf("%lf", &x);
    printf("Precisao: ");
    scanf("%lf", &precisao);

    x = x - (function(x)/derivada(x));
    y = function(x);
    k = 1;

    while(fabs(y) > precisao)
    {
        k++;
        
        x = x - (function(x)/derivada(x));
        y = function(x);
    }

    printf("X: %lf\n", x);
    printf("f(X): %lf\n", y);
    printf("Interacao: %d\n", k);

    return 0;
}