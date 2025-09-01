#include <stdio.h>
#include <math.h>

double function(double x)
{
    return exp(x) + x*x - 2;
}

int main()
{
    int k;
    double a, b, fa, fb, x, y, precisao;

    printf("Intervalo: ");
    scanf("%lf %lf", &a, &b);
    printf("Precisao: ");
    scanf("%lf", &precisao);

    fa = function(a);
    fb = function(b);
    x = (a*fabs(fb)+b*fabs(fa))/(fabs(fa) + fabs(fb));
    y = function(x);
    k = 0;

    while(fabs(y) > precisao)
    {
        k++;

        if(sameSign(y, a))
        {
            a = x;
            fa = function(a);
        }
        else
        {
            b = x;
            fb = function(b);
        }
        
        x = (a*fabs(fb)+b*fabs(fa))/(fabs(fa) + fabs(fb));
        y = function(x);
    }

    printf("X: %lf\n", x);
    printf("f(X): %lf\n", y);
    printf("Interacao: %d\n", k);

    return 0;
}