//File: roate_linear.c
//Oliver Lynch

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
#include <cstring>

#define IMG_HEIGHT (920)
#define IMG_WIDTH (690)

typedef unsigned char UINT8;

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

int main(int argc, char *argv[]){

    DIR* FD;
    struct dirent* in_file;

    char file[30], infolder[15]="cards_3x4_ppm/", outfolder[22]="cards_3x4_ppm_rotate/";
    int fdin, fdout, bytesRead=0, bytesWritten=0, bytesLeft=0, readcnt=0, writecnt=0;

    //Start the clock
    struct timespec start, now;
    double fstart, fnow;
    clock_gettime(CLOCK_MONOTONIC, &start);
    fstart = (double)start.tv_sec  + (double)start.tv_nsec / 1000000000.0;

    //open the directory
    if (NULL != (FD = opendir (infolder))) {
        //Open the file
        while((in_file=readdir(FD))){ 

            //dont open other folders
            if (!strcmp (in_file->d_name, "."))
                continue;
            if (!strcmp (in_file->d_name, ".."))    
                continue;

            //copy full file path to file
            strcpy(file,infolder);
            strcat(file,in_file->d_name);

            //open input file
            if((fdin = open(file, O_RDONLY, 0644)) < 0){
                printf("Error opening %s\n", in_file->d_name);
                exit(-1);
            }

            //copy full file path to file
            strcpy(file,outfolder);
            strcat(file,in_file->d_name);

            //open output file
            if((fdout = open(file, (O_RDWR | O_CREAT), 0666)) < 0){
                printf("Error opening %s\n", argv[1]);
                exit(-1);
            }

            //read in image from file
            bytesRead=0;
            bytesLeft=IMG_HEIGHT*IMG_WIDTH*3;
            readcnt=0;

            do{
                bytesRead=read(fdin, (void *)&RGB[bytesRead], bytesLeft);
                bytesLeft -= bytesRead;
                readcnt++;
            }while((bytesLeft > 0) && (readcnt < 3));

            //create in memory copy from input by channel
            for(int i = 0, pixel = 0; i < IMG_HEIGHT; i++){
                for(int j = 0; j < IMG_WIDTH; j++){
                    R[i][j] = RGB[pixel+0];
                    G[i][j] = RGB[pixel+1];
                    B[i][j] = RGB[pixel+2];
                    pixel+=3;
                }
            }

            //rotate image
            for(int i = 0; i < IMG_HEIGHT; i++){
                for(int j = 0; j < IMG_WIDTH; j++){
                    NewR[j][IMG_HEIGHT-1-i] = R[i][j];
                    NewG[j][IMG_HEIGHT-1-i] = G[i][j];
                    NewB[j][IMG_HEIGHT-1-i] = B[i][j];
                }
            }

            //Save the image
            // create in memory copy from input by channel
            for(int i = 0, pixel = 0; i < IMG_WIDTH; i++){
                for(int j = 0; j < IMG_HEIGHT; j++){
                    RGB[pixel+0] = NewR[i][j];
                    RGB[pixel+1] = NewG[i][j];
                    RGB[pixel+2] = NewB[i][j];
                    pixel+=3;
                }
            }
            
            //make new header
            std::string tmp = "P6\n920 690\n255\n#Oliver Lynch";
            for(int i=0; i<=tmp.size(); i++){
                header[i] = tmp[i];
            }
            //printf("newheader = %s\n\n", header);

            //write header
            write(fdout, (void *)header, tmp.size());
            
            //write image
            bytesWritten=0;
            bytesLeft=IMG_HEIGHT*IMG_WIDTH*3;
            writecnt=0;

            do{
                bytesWritten=write(fdout, (void *)&RGB[bytesWritten], bytesLeft);
                bytesLeft -= bytesWritten;
                writecnt++;
            } while((bytesLeft > 0) && (writecnt < 3));

            //close input and output file           
            close(fdin);
            close(fdout);
        }
    }
    
    //End the clock
    clock_gettime(CLOCK_MONOTONIC, &now);
    fnow = (double)now.tv_sec  + (double)now.tv_nsec / 1000000000.0;
    printf("Total time: %lf\n", fnow-fstart);


    return 0;
} 