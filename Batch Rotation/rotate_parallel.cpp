//File: roate_parallel.c
//Oliver Lynch

/*
Parallel percentage: 99.0455%
Cores: 4
expected speedup: 3.89x
Actual Speedup: 3.38x
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <pthread.h>


#define Thread_Count 4

#define IMG_HEIGHT (920)
#define IMG_WIDTH (690)

typedef unsigned char UINT8;

struct thread_data{
    int fdin, fdout, bytesRead, bytesWritten, bytesLeft, readcnt, writecnt;    
    //PPM types
    UINT8 header[70];
    UINT8 R[IMG_HEIGHT][IMG_WIDTH];
    UINT8 G[IMG_HEIGHT][IMG_WIDTH];
    UINT8 B[IMG_HEIGHT][IMG_WIDTH];
    UINT8 NewR[IMG_WIDTH][IMG_HEIGHT];
    UINT8 NewG[IMG_WIDTH][IMG_HEIGHT];
    UINT8 NewB[IMG_WIDTH][IMG_HEIGHT];
    
    //PPM image array with channels
    UINT8 RGB[IMG_HEIGHT*IMG_WIDTH*3];
};


void *doWork(void* data){
    struct thread_data *mydata;
    mydata = (struct thread_data *)data;

    //read in image from file
    mydata->bytesRead=0;
    mydata->bytesLeft=IMG_HEIGHT*IMG_WIDTH*3;
    mydata->readcnt=0;

    do{
        mydata->bytesRead=read(mydata->fdin, (void *)&mydata->RGB[mydata->bytesRead], mydata->bytesLeft);
        mydata->bytesLeft -= mydata->bytesRead;
        mydata->readcnt++;
    }while((mydata->bytesLeft > 0) && (mydata->readcnt < 3));

    //create in memory copy from input by channel
    for(int i = 0, pixel = 0; i < IMG_HEIGHT; i++){
        for(int j = 0; j < IMG_WIDTH; j++){
            mydata->R[i][j] = mydata->RGB[pixel+0];
            mydata->G[i][j] = mydata->RGB[pixel+1];
            mydata->B[i][j] = mydata->RGB[pixel+2];
            pixel+=3;
        }
    }

    //rotate image
    for(int i = 0; i < IMG_HEIGHT; i++){
        for(int j = 0; j < IMG_WIDTH; j++){
           mydata->NewR[j][IMG_HEIGHT-1-i] = mydata->R[i][j];
            mydata->NewG[j][IMG_HEIGHT-1-i] = mydata->G[i][j];
            mydata->NewB[j][IMG_HEIGHT-1-i] = mydata->B[i][j];
        }
    }

    // create in memory copy from input by channel
    for(int i = 0, pixel = 0; i < IMG_WIDTH; i++){
        for(int j = 0; j < IMG_HEIGHT; j++){
            mydata->RGB[pixel+0] = mydata->NewR[i][j];
            mydata->RGB[pixel+1] = mydata->NewG[i][j];
            mydata->RGB[pixel+2] = mydata->NewB[i][j];
            pixel+=3;
        }
    }
    
    //make new header
    std::string tmp = "P6\n920 690\n255\n#Oliver Lynch";
    for(int i=0; i<=tmp.size(); i++){
        mydata->header[i] = tmp[i];
    }

    //write header
    write(mydata->fdout, (void *)mydata->header, tmp.size());
    
    //write image
    mydata->bytesWritten=0;
    mydata->bytesLeft=IMG_HEIGHT*IMG_WIDTH*3;
    mydata->writecnt=0;

    do{
        mydata->bytesWritten=write(mydata->fdout, (void *)&mydata->RGB[mydata->bytesWritten], mydata->bytesLeft);
        mydata->bytesLeft -= mydata->bytesWritten;
        mydata->writecnt++;
    } while((mydata->bytesLeft > 0) && (mydata->writecnt < 3));

    //close input and output file           
    close(mydata->fdin);
    close(mydata->fdout);
    pthread_exit(NULL);

}


int main(){
    DIR* FD;
    struct dirent* in_file;

    char file[30], infolder[15]="cards_3x4_ppm/", outfolder[22]="cards_3x4_ppm_rotate/";

    pthread_t threads[Thread_Count];
    static struct thread_data mydata[52];
    int cardnumb = 0;
    int rc;

    //Start the clock
    struct timespec start, now;
    double fstart, fnow;
    clock_gettime(CLOCK_MONOTONIC, &start);
    fstart = (double)start.tv_sec  + (double)start.tv_nsec / 1000000000.0;
    
    //open the directory
    if (NULL != (FD = opendir (infolder))) {
        //Open the file
        while(cardnumb<=52 && (in_file=readdir(FD))){ 

            //dont open other folders
            if (!strcmp (in_file->d_name, "."))
                continue;
            if (!strcmp (in_file->d_name, ".."))    
                continue;

            //copy full file path to file
            strcpy(file,infolder);
            strcat(file,in_file->d_name);

            //open input file
            if((mydata[cardnumb].fdin = open(file, O_RDONLY, 0644)) < 0){
                printf("Error opening folder\n");
                exit(-1);
            }

            //copy full file path to file
            strcpy(file,outfolder);
            strcat(file,in_file->d_name);

            //open output file
            if((mydata[cardnumb].fdout = open(file, (O_RDWR | O_CREAT), 0666)) < 0){
                printf("Error opening file\n");
                exit(-1);
            }else{
                cardnumb++;
            }
        }
        
        //Get clock time for %parallel 
        clock_gettime(CLOCK_MONOTONIC, &now);
        fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
        double linartime = fnow-fstart; 

        //spin up threads
        for(int i=0, j=0; i < 52; i++ ){
            rc = pthread_create(&threads[j], NULL, doWork, (void*)&mydata[i]);
            j++;
            if(j > Thread_Count){ //since only doing Thread_Count threads at a time gotta close them before re using them 
                for(int ii = 0; ii<Thread_Count; ii++){
                    rc = pthread_join(threads[ii], NULL);
                }
                j=0;
            }
        }

        //End the clock
        clock_gettime(CLOCK_MONOTONIC, &now);
        fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
        double totaltime = fnow-fstart; 
        printf("Number of Threads: %d\n", Thread_Count);
        printf("Percentage parallel(by time): %lf\n", 1-(linartime/totaltime));
        printf("Total time: %lf\n", totaltime);
    }

    pthread_exit(NULL);
    return 0;
} 