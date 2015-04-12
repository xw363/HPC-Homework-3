/*
 * The Gauss-Seidel method
 */
#include "laplace.h"

int main(int argc, char** argv)
{
    int N = atoi(argv[1]);
    double h = 1.0 / (N + 1);
    double* u = get_u_0(N);

    double res = residual(u, N, h);
    double res_min = res * RESIDUAL_FACTOR;

    int i, j, k = 0;
    double aui;  /* Placeholder for sum of a_ij * u_j */
    while (res > res_min && k < MAX_ITERATION) {
        for (i = 0; i < N; ++i) {
            aui = 0.0;

            if (i == 0)
                aui = -u[1] / (h * h);
            else if (i == N - 1)
                aui = -u[N - 2] / (h * h);
            else
                aui = -(u[i - 1] + u[i + 1]) / (h * h);

            u[i] = (1 - aui) / 2 * h * h;
        }

        res = residual(u, N, h);
        printf("%.8f\n", res);
        k++;
    }

    if (res > res_min)
        printf("Initial residual decreased by: %.8f\n",
                res / (res_min / RESIDUAL_FACTOR));
    printf("Number of iterations: %d\n", k);

    free(u);

    return 0;
}

