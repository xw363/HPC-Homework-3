all: jacobi
jacobi: jacobi.c laplace
	gcc -c jacobi-omp.c -fopenmp -o jacobi-omp.o
	gcc jacobi-omp.o laplace.o -fopenmp -lm -o jacobi-omp
laplace:
	gcc -c laplace.c -o laplace.o

