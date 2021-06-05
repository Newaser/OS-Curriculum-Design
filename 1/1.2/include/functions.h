#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<conio.h>
#include"definitions.h"

void countDown(float* sec_ptr, float max_sec, char mode){
    if(mode == '-'){
        //content: count-down in '-' mode
    }else if(mode == '+'){
        //content; count-down in '+' mode
    }else{
        perror("Invalid mode type!\n");

    }
}

int initSem(){
    return semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
}

void pause(char *prompt, int ascii){
    printf("%s\n", prompt);
    if(ascii == Null){
        getch();
    }else {
        while(getch() != ascii);
    }
}

void* sharedMem(size_t size){  //content: return a sized, anonymous block of shared memory(mmap)
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

QUEUE* importCars(path f_path){
    //content: import car data from a txt file
    //content: if the amout of cars from any direction exceeds 5, error
}