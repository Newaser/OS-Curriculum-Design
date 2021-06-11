#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include"queue.h"

void countDown(double* sec_ptr, double max_sec, char mode){  //count down certain seconds
    int times = (int)(max_sec/SleepGranu);  //times of "for" loop
    
    if(mode == '-'){
    	*sec_ptr = -max_sec;
        for(int i=0; i < times; i++){
            usleep(SleepGranu*1000000);
        	*sec_ptr += SleepGranu;
        }
    }else if(mode == '+'){
        *sec_ptr = max_sec;
        for(int i=0; i < times; i++){
        	usleep(SleepGranu*1000000);
        	*sec_ptr -= SleepGranu;
        }
    }else{
        perror("Invalid mode type!\n");

    }
}

int initSem(){
    return semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
}

void* sharedMem(size_t size){  //content: return a sized, anonymous block of shared memory(mmap)
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

QUEUE* importCars(path f_path){
    //content: import car data from a txt file
    //content: if the amout of cars from any direction exceeds 5, error
}
