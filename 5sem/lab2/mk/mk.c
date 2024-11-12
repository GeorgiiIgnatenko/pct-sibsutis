#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

//#define N 10000000
#define N 100000000

double func(double x, double y)
{
    return (x/pow(y,2));
}

double getrand()
{
    return (double)rand() / RAND_MAX;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, commsize;
    const int n = N;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    srand(rank);
    int in = 0;
    double s = 0;
    double start_time = 0;
    double finish_time = 0;

    if (rank == 0)
        start_time = MPI_Wtime();

    for (int i = rank; i < n; i += commsize)
    {
        double x = getrand();
        double y = 2 + getrand() * 3;
        if (y <= 5)
        {
            in++;
            s += func(x, y);
        }
    }

    int gin = 0;
    MPI_Reduce(&in, &gin, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    double gsum = 0.0;
    MPI_Reduce(&s, &gsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
    {
        double v = gin / n;
        double res = v * gsum / gin;
        finish_time = MPI_Wtime();
        printf("Time: %f Result: %.12f, n %d\n", finish_time - start_time, res, n);
        double speedup = 10.625856/(finish_time - start_time);
        printf("Speedup: %lf", speedup);
    }
    MPI_Finalize();
    return 0;
}
