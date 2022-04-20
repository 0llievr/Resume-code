// x0 the value of root at nth iteration -2 or 4 or 7
// allowed error 0.0001
// itterations 10

#include<stdio.h>
#include<math.h>
#include <time.h>

double f(double x)
{
    //return x*log10(x) - 1.2; //Original
    return (pow(-x,3.0) + (9.7 * pow(x,2)) - (1.3*x) -105.7 ); //mine
    //return (pow(x,2)-10); //test
}

double df (double x)
{
    //return log10(x) + 0.43429; //Original 
    return ((-(3.0*pow(x,2)) + ((97.0*x)/5.0) - (13.0/10.0))); //mine
    //return 2*x; //test
}

int main(void)
{
    int itr, maxmitr;
    double h, x0, x1, allerr;
    printf("\nEnter x0, allowed error, and maximum iterations\n");
    scanf("%lf %lf %d", &x0, &allerr, &maxmitr);
   
    struct timespec start, end;
    double fstart, fend;

    printf("Multiplication of given two matrices is:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (itr=1; itr<=maxmitr; itr++)
    {
        h=f(x0)/df(x0);
        x1=x0-h;
        printf(" At Iteration no. %3d, x = %9.6f\n", itr, x1);
        if (fabs(h) < allerr)
        {
            printf("After %3d iterations, root = %8.6f\n", itr, x1);
            clock_gettime(CLOCK_MONOTONIC, &end);
            fstart=start.tv_sec + (start.tv_nsec / 1000000000.0);
            fend=end.tv_sec + (end.tv_nsec / 1000000000.0);
            printf("In %lf seconds \n",(fend-fstart));
            return 0;
        }
        x0=x1;
    }
    printf(" The required solution does not converge or iterations are insufficient\n");
    return 1;
}