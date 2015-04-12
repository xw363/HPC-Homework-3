/*
 * The OpenMP version of Gauss-Seidel method
 */
#include "laplace.h"
#include <sys/time.h>
#include <omp.h>

int main(int argc, char** argv)
{
    int N = atoi(argv[1]);
    double h = 1.0 / (N + 1);
    double* u = get_u_0(N);

    double res = residual(u, N, h);
    double res_min = res * RESIDUAL_FACTOR;

    int i, j, k = 0;
    double aui;  /* Placeholder for sum of a_ij * u_j */

    struct timeval start, finish;  /* Times that the the Jacobi iterations
                                      start and finish */
    double total_time;  /* Total running time */

    /* Mark start time */
    gettimeofday(&start, NULL);

    while (res > res_min && k < MAX_ITERATION) {
#pragma omp parallel private (i, aui)
        {
            /* Update even elements first */
#pragma omp for
            for (i = 0; i < N; i += 2) {
                aui = 0.0;

                if (i == 0)
                    aui = -u[1] / (h * h);
                else if (i == N - 1)
                    aui = -u[N - 2] / (h * h);
                else
                    aui = -(u[i - 1] + u[i + 1]) / (h * h);

                u[i] = (1 - aui) / 2 * h * h;
            }

            /* Update odd elements */
#pragma omp for
            for (i = 1; i < N; i += 2) {
                aui = 0.0;

                if (i == 0)
                    aui = -u[1] / (h * h);
                else if (i == N - 1)
                    aui = -u[N - 2] / (h * h);
                else
                    aui = -(u[i - 1] + u[i + 1]) / (h * h);

                u[i] = (1 - aui) / 2 * h * h;
            }
        }

        res = residual(u, N, h);
        res = residual(u, N, h);
        printf("%.8f\n", res);
        k++;
    }

    /* Mark finish time */
    gettimeofday(&finish, NULL);

    if (res > res_min)
        printf("Initial residual decreased by: %.8f\n",
                res / (res_min / RESIDUAL_FACTOR));
    printf("Number of iterations: %d\n", k);

    total_time = finish.tv_sec - start.tv_sec
                 + (finish.tv_usec - start.tv_usec) / 1e6;
    printf("Jacobi solver running time: %.8f seconds\n", total_time);

    free(u);

    return 0;
}

