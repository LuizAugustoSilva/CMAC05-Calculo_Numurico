#include <stdio.h>
#include <math.h>

double function(double x)
{
    return exp(x) + x*x - 2;
}

int sameSign(double y, double a)
{
    double fa = function(a);

    if((fa > 0 && y > 0) || (fa < 0 && y < 0))
        return 1;
    else
        return 0;
}

int main()
{
    int k;
    double a, b, x, y, precisao;

    printf("Intervalo: ");
    scanf("%lf %lf", &a, &b);
    printf("Precisao: ");
    scanf("%lf", &precisao);

    x = (a+b)/2;
    y = function(x);
    k = 0;

    while(fabs(y) > precisao)
    {
        k++;

        if(sameSign(y, a))
            a = x;
        else
            b = x;
        
        x = (a+b)/2;
        y = function(x);
    }

    printf("X: %lf\n", x);
    printf("f(X): %lf\n", y);
    printf("Interacao: %d\n", k);

    return 0;
}