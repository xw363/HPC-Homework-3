/*
 * The OpenMP version of Jacobi method
 */
#include <string.h>
#include <sys/time.h>
#include <omp.h>
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
    double *u_old = (double*) malloc(N * sizeof(double));

    struct timeval start, finish;  /* Times that the the Jacobi iterations
                                      start and finish */
    double total_time;  /* Total running time */

    /* Mark start time */
    gettimeofday(&start, NULL);

    while (res > res_min && k < MAX_ITERATION) {
        memcpy(u_old, u, sizeof(double) * N);

#pragma omp parallel for private(i, aui)
        for (i = 0; i < N; ++i) {
            aui = 0.0;

            if (i == 0)
                aui = -u_old[1] / (h * h);
            else if (i == N - 1)
                aui = -u_old[N - 2] / (h * h);
            else
                aui = -(u_old[i - 1] + u_old[i + 1]) / (h * h);

            u[i] = (1 - aui) / 2 * h * h;
        }

        res = residual(u, N, h);
        printf("%.8f\n", res);
        k++;
    }

    /* Mark finish time */
    gettimeofday(&finish, NULL);

    if (res > res_min)
        printf("Initial residual decreased by: %.8f\n",
                1 - res / (res_min / RESIDUAL_FACTOR));
    printf("Number of iterations: %d\n", k);

    total_time = finish.tv_sec - start.tv_sec
                 + (finish.tv_usec - start.tv_usec) / 1e6;
    printf("Jacobi solver running time: %.8f seconds\n", total_time);

    free(u);
    free(u_old);

    return 0;
}

