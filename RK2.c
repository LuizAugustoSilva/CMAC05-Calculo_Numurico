#include <stdio.h>
#include <math.h>

double f(double x, double y)
{
    return (2000-2*y)/(200-x);
}

double rk2(double x0, double y0, double h, int n)
{
    int i;
    double x = x0, y = y0;
    double k1, k2;

    printf("Iteracao 0: x = %.5f  y = %.5f\n", x, y);
    for(i = 1; i <= n; i++)
    {
        k1 = f(x, y);
        k2 = f(x + h/2.0, y + (h/2.0) * k1);
        y = y + h * k2;
        x = x + h;
        printf("Iteracao %d: x = %.5f  y = %.5f\n", i, x, y);
    }

    return y;
}

int main()
{
    double x0, y0, xf, h, resultado;
    int n;

    printf("=== Runge-Kutta 2 ordem ===\n");

    printf("Digite x0: ");
    scanf("%lf", &x0);

    printf("Digite y(x0): ");
    scanf("%lf", &y0);

    printf("Digite o ponto final xf: ");
    scanf("%lf", &xf);

    printf("Numero de subintervalos (n): ");
    scanf("%d", &n);

    h = (xf - x0) / n;
    printf("\nPasso h = %.10f\n\n", h);

    resultado = rk2(x0, y0, h, n);
    printf("\nResultado final aproximado: y(%.6f) = %.10f\n", xf, resultado);

    return 0;
}
