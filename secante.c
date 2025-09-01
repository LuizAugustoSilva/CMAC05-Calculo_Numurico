#include <stdio.h>
#include <math.h>

double function(double x)
{
    return cos(x) - x*x;
}

int main()
{
    int k;
    double x0, x1, fx0, fx1, x, y, precisao;

    printf("Intervalo: ");
    scanf("%lf %lf", &x0, &x1);
    printf("Precisao: ");
    scanf("%lf", &precisao);

    fx0 = function(x0);
    fx1 = function(x1);
    x = x1 - (fx1/(fx1-fx0)) * (x1-x0);
    y = function(x);
    k = 0;

    while(fabs(y) > precisao)
    {
        x0 = x1;
        x1 = x;
        fx0 = function(x0);
        fx1 = function(x1);

        x = x1 - (fx1/(fx1-fx0)) * (x1-x0);
        y = function(x);
        k++;
    }

    printf("X: %lf\n", x);
    printf("f(X): %lf\n", y);
    printf("Interacao: %d\n", k);

    return 0;
}