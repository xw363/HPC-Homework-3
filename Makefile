all: jacobi gs
jacobi: jacobi-omp.c laplace
	gcc -c jacobi-omp.c -fopenmp -o jacobi-omp.o
	gcc jacobi-omp.o laplace.o -fopenmp -lm -o jacobi-omp
gs: gs-omp.c laplace
	gcc -c gs-omp.c -fopenmp -o gs-omp.o
	gcc gs-omp.o laplace.o -fopenmp -lm -o gs-omp
laplace:
	gcc -c laplace.c -o laplace.o
clean:
	rm *.o
	rm jacobi-omp
	rm gs-omp

