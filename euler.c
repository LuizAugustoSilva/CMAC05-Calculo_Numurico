#include <stdio.h>

// =======================================================
//  Edite aqui a sua EDO: y' = f(x, y)
// =======================================================
double f(double x, double y) {
    // EXEMPLO: y' + 2y = 0  →  y' = -2y
    return y;
}

// =======================================================
// Método de Euler simples
// =======================================================
double euler_simples(double x0, double y0, double h, int n) {
    double x = x0, y = y0;

    printf("Iteração 0: x = %.5f  y = %.5f\n", x, y);
    for (int i = 1; i <= n; i++) {
        y = y + h * f(x, y);
        x = x + h;

        printf("Iteração %d: x = %.5f  y = %.5f\n", i, x, y);
    }

    return y;
}

// =======================================================
// Método de Euler estendido (Heun)
// =======================================================
double euler_estendido(double x0, double y0, double h, int n) {
    double x = x0, y = y0;
    double k1, k2;

    printf("Iteracao 0: x = %.5f  y = %.5f\n", x, y);
    for (int i = 1; i <= n; i++)
    {
        k1 = f(x, y);
        k2 = f(x + h, y + h * k1);

        y = y + (h / 2.0) * (k1 + k2);
        x = x + h;

        printf("Iteracao %d: x = %.5f  y = %.5f\n", i, x, y);
    }

    return y;
}

// =======================================================
// Programa principal
// =======================================================
int main() {
    double x0, y0, xf;
    int n, metodo;

    printf("=== Metodo de Euler (Simples e Estendido) ===\n");

    printf("Digite x0: ");
    scanf("%lf", &x0);

    printf("Digite y(x0): ");
    scanf("%lf", &y0);

    printf("Digite o ponto final xf: ");
    scanf("%lf", &xf);

    printf("Numero de subintervalos: ");
    scanf("%d", &n);

    printf("Metodo:\n1 - Euler simples\n2 - Euler estendido\nEscolha: ");
    scanf("%d", &metodo);

    double h = (xf - x0) / n;

    printf("\nPasso h = %.6f\n\n", h);

    double resultado;

    if (metodo == 1) {
        resultado = euler_simples(x0, y0, h, n);
    } else {
        resultado = euler_estendido(x0, y0, h, n);
    }

    printf("\nResultado final aproximado: y(%.5f) = %.10f\n", xf, resultado);

    return 0;
}
