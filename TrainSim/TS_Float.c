//Oliver Lynch
/* File:     TS_Float.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal 
 *           rule.  In this version the endpoints of the interval and
 *           the number of trapezoids are hardwired.
 *
 * Input:    None.
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o TS_Float TS_Float.c
 * Run:      mpiexec -n <number of processes> ./TS_Float
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x), a, b, and n are all hardwired.
 *
 * IPP:   Section 3.2.2 (pp. 96 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

float ex4_accel(float time){
    // computation of time scale for 1800 seconds
    static float tscale=1800.0/(2.0*M_PI);
    // determined such that acceleration will peak to result in translation of 122,000.0 meters
    static float ascale=0.2365893166123;
 
    return (sin(time/tscale)*ascale);
}

// determined based on known anti-derivative of ex4_accel function
float ex4_vel(float time){
    // computation of time scale for 1800 seconds
    static float tscale=1800.0/(2.0*M_PI);
    // determined such that velocity will peak to result in translation of 122,000.0 meters
    static float vscale=0.2365893166123*1800.0/(2.0*M_PI);
 
    return ((-cos(time/tscale)+1)*vscale);
}

/* Calculate local integral  */
float Trap(float left_endpt, float right_endpt, int trap_count, 
   float base_len);    

/* Function we're integrating */
float f(float x); 

int main(void) {
    int my_rank, comm_sz, n = 1801/.01, local_n;   
    float a = 0.0, b = 1801, h, local_a, local_b;
    float local_float, total_distance, end_velocity;

    /* Let the system do what it needs to start up MPI */
    MPI_Init(NULL, NULL);

    /* Get my process rank and total processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    h = (b-a)/n;          /* h is the same for all processes */
    local_n = n/comm_sz;  /* So is the number of trapezoids  */

    /* Length of each process' interval of
        * integration = local_n*h.  So my interval
        * starts at: */
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    local_float = Trap(local_a, local_b, local_n, h);

    
    /* Add up the integrals calculated by each process */
    MPI_Reduce(&local_float, &total_distance, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    //get ending velocity
    if (my_rank == comm_sz - 1) {
        end_velocity = ex4_accel(local_b - 1);
    }

    /* Print the result */
    if(my_rank == 0){
        printf("TS_Float: \n\tfinal velocity = %lf\n\tfinal position = %lf\n", 
            end_velocity, total_distance);
    }

    /* Shut down MPI */
    MPI_Finalize();

    return 0;
} /*  main  */


/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
float Trap(
      float left_endpt  /* in */, 
      float right_endpt /* in */, 
      int    trap_count  /* in */, 
      float base_len    /* in */) {
    float estimate, x; 
    int i;

    estimate = (f(left_endpt) + f(right_endpt))/2.0;
    for (i = 1; i <= trap_count-1; i++) {
        x = left_endpt + i*base_len;
        estimate += f(x);
    }
    estimate = estimate*base_len;

    return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
float f(float x) {
    return ex4_vel(x);
} /* f */