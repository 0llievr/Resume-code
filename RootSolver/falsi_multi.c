//x0, x1 – the limits within which the root lies
// allowed error 0.0001
// itterations 10




#include<stdio.h>
#include<math.h>
#include <time.h>

double f(double x)
{
    //return cos(x) - x*exp(x);
    return cos(pow(x,2)); //mine
}

void regula (double *x, double x0, double x1, double fx0, double fx1, int *itr)
{
    *x = x0 - ((x1 - x0) / (fx1 - fx0))*fx0;
    ++(*itr);
    //printf("Iteration no. %3d X = %7.5f \n", *itr, *x);
}

int main(void)
{
    int maxmitr=10;
    double x0,x1,allerr=0.0001;
    printf("\nEnter range start, range end\n");
    scanf("%lf %lf", &x0, &x1);
    //regula (&x2, x0, x1, f(x0), f(x1), &itr);

    struct timespec start, end;
    double fstart, fend;

    printf("Multiplication of given two matrices is:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
        
    double last = 0;

    for(double i = x0; i < x1-0.05; i+=.05){
        int itr = 0;
        double x2, x3;
        double xx0 = i;
        double xx1 = xx0 +.05;

        regula (&x2, xx0, xx1, f(xx0), f(xx1), &itr);
        do
        {
            if (f(xx0)*f(x2) < 0)
                xx1=x2;
            else
                xx0=x2;
            regula (&x3, xx0, xx1, f(xx0), f(xx1), &itr);
            if (fabs(x3-x2) < allerr)
            {
                //if(fabs(x3-last) <= .0000001){ does not work for some reason
                    last=x3;
                    printf("After %d iterations, root = %f\n", itr, x3);
                //}
                break;
            }
            x2=x3;
        }while (itr<maxmitr);
        //break goes here
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    fstart=start.tv_sec + (start.tv_nsec / 1000000000.0);
    fend=end.tv_sec + (end.tv_nsec / 1000000000.0);
    printf("In %lf seconds \n",(fend-fstart));
    return 1;
}