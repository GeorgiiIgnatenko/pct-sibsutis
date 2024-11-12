#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//#define N 10000000
#define N 100000000

double getrand()
{
    return (double)rand() / RAND_MAX;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double func(double x, double y)
{
    return (x/pow(y,2));
}

int main()
{
    int in = 0;
    double s = 0;
    double t = wtime();
    for (int i = 0; i < N; i++)
    {
        double x = getrand();
        double y = 2 + getrand() * 3;
        if (y <= 5)
        {
            in++;
            s += func(x, y);
        }
    }
    double v = 3.0 * in / N;
    double res = v * s / in;
    t = wtime() - t;
    printf("Elapsed time (serial): %.6f sec.\n", t);
    printf("Result: %.12f, N %d\n", res, N);
    return 0;
}
