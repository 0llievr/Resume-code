//Oliver Lynch
//mpirun -n 4 -ppn 2 -f ../c2_hosts ./LRS_Float

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

int main(){
    float time, dt = .01; // dt=1.0 is the default to match spreadsheet
    int tsize = 1801;
    int istep=0;
    float PosStep=0, VelStep=0, total_distance=0, final_velocity=0;
    int my_rank, comm_sz;
    
    MPI_Init(NULL, NULL); //initalize the MPI execution environment
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //Retrieve total processes avaliable
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //determine the rank of the calling process
    
    //divide intagration steps by processes to divide up work
    int total_steps = tsize/dt;
    int section = total_steps/comm_sz; //get section size based off total processes
    int start = my_rank * section; //section start
    int end = start + section; //section end

    //printf("%d section:%d start:%d end:%d\n", my_rank, section, start, end);

    for(istep=start; istep < end; istep++){
	    time = (float)istep * dt;
        VelStep = ex4_vel(time); 
        PosStep += (VelStep * dt);
    }

    MPI_Reduce(&PosStep, &total_distance, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD); 
    
    //Not the correct way to do this but it works
    MPI_Reduce(&VelStep, &final_velocity, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);
    
    if(my_rank == 0){
        printf("LRS_float: \n\tfinal velocity = %lf\n\tfinal position = %lf\n", 
            final_velocity, total_distance);
    }

    MPI_Finalize();
    return 0;
}