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
    int times = (int)(max_sec/CountDownGranu);  //times of counting a granule of time
    
    if(mode == '-'){
    	*sec_ptr = -max_sec;
        for(int i=0; i < times; i++){
            usleep(CountDownGranu*1000000);
        	*sec_ptr += CountDownGranu;
        }
    }else if(mode == '+'){
        *sec_ptr = max_sec;
        for(int i=0; i < times; i++){
        	usleep(CountDownGranu*1000000);
        	*sec_ptr -= CountDownGranu;
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
    /*
    Import car data from a txt file,
    if the amount of cars from any direction exceeds 5, error
    */
    QUEUE *cars = (QUEUE*) malloc(sizeof(QUEUE));
    cars = createQueue(MaxCars*4);
    car car_i;
    char from_i[16];
    int orientations[4] = {0};
    
    void check_car(quaOrient ori){  //check and enqueue the data of car i
        if(car_i.car_id < 0){
            perror("Exists one car whose car ID is invalid!\n");
        }else if(orientations[ori] >= MaxCars){
            perror("Exists one direction whose car\'s amount exceeds its max!\n");
        }else if(MaxLightSeconds - car_i.est_time <= SafeSeconds){
            perror("Exists one car which is too slow to pass the road!\n");
        }else {
            car_i.from = ori;
            orientations[ori]++;
            enQueue(car_i, cars);
        }
    }
    
    FILE *data_f = fopen(f_path, "r");
    while(True){
        fscanf(data_f, "%d %s %lf", &car_i.car_id, from_i, &car_i.est_time);
        if(feof(data_f)){  //if all of the data imported, break out
            break;
        }else {
        
            for(int ori_i=0;ori_i<4+1;ori_i++){  //get car's orientation
                if(ori_i > 4){
                    perror("Exists one car whose orientation is invalid!\n");
                }else if(strcmp(from_i, ORIENTATIONS[ori_i]) == 0){
                    check_car(ori_i);
                }
            }

        }
    }
    fclose(data_f);
    
    return cars;
}



