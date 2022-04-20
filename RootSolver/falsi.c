//x0, x1 – the limits within which the root lies
// allowed error 0.0001
// itterations 10

#include<stdio.h>
#include<math.h>
#include <time.h>

double f(double x)
{
    //return cos(x) - x*exp(x);
    return (pow(-x,3.0) + (9.7 * pow(x,2)) - (1.3*x) -105.7 ); //mine
}

void regula (double *x, double x0, double x1, double fx0, double fx1, int *itr)
{
    *x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
    ++(*itr);
    printf("Iteration no. %3d X = %7.5f \n", *itr, *x);
}

int main(void)
{
    int itr = 0, maxmitr;
    double x0,x1,x2,x3,allerr;
    printf("\nEnter the values of x0, x1, allowed error and maximum iterations:\n");
    scanf("%lf %lf %lf %d", &x0, &x1, &allerr, &maxmitr);
    regula (&x2, x0, x1, f(x0), f(x1), &itr);

    struct timespec start, end;
    double fstart, fend;

    printf("Multiplication of given two matrices is:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);

    do
    {
        if (f(x0)*f(x2) < 0)
            x1=x2;
        else
            x0=x2;
        regula (&x3, x0, x1, f(x0), f(x1), &itr);
        if (fabs(x3-x2) < allerr)
        {
            printf("After %d iterations, root = %6.4f\n", itr, x3);
            clock_gettime(CLOCK_MONOTONIC, &end);
            fstart=start.tv_sec + (start.tv_nsec / 1000000000.0);
            fend=end.tv_sec + (end.tv_nsec / 1000000000.0);
            printf("In %lf seconds \n",(fend-fstart));
            return 0;
        }
        x2=x3;
    }
    while (itr<maxmitr);
    printf("Solution does not converge or iterations not sufficient:\n");
    return 1;
}