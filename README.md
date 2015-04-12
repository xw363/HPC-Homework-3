# HPC Homework 3
Homework 3, High Performance Computing (NYU Spring 2015)

## Compile the OpenMP version of Jacobi and Gauss-Seidel solvers
Type `make` in a terminal.

## Run the solvers
Enter `./jacobi-omp N` and `./gs-omp N`, where `N` is the size of vector.

## Result from Stampede
`jacobi-omp.txt` and `gs-omp.txt` contain running time of the two solvers with different number of threads on Stampede. The programs are compiled using the Intel compiler instead of gcc. Each program runs with a number of threads 10 times. The only output from both solvers is the running time. All other output to `stdout` are commented out in the source code before compilation.
