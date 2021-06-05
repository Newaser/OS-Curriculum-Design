#include <unistd.h>

#include"../include/functions.h"
#include"../include/PV.h"

//shared variables:
double *sec_ptr;       //pointer of seconds remaining of traffic lights
                       //(no semaphore because: cars need real-time reading to it, meanwhile lights need real-time writing to it)
QUEUE *cars;           //mixed cars from 4 directions
QUEUE *car_queues[4];  //4 queues of cars for each direction

//semaphores:
semaphore mutexCars;  //semaphore for cars
semaphore mutexCqs[4];  //semaphores for each car_queue
semaphore roads[4];  //4 mutex roads: North, South, East, West

int main(){
    /*
       Traffic Lights Algorithm: ...
    */
    void lights(double* sec_ptr, semaphore* roads);  //traffic lights process
    void car(double* sec_ptr, QUEUE* cars, QUEUE** cqs, semaphore mutexCars, semaphore* mutexCqs, semaphore* roads);  // car process
    
    //Shared Memory Allocations:
    sec_ptr = (double*)sharedMem(sizeof(double));
    cars = (QUEUE*)sharedMem(sizeof(QUEUE));
    car_queues = (QUEUE*)sharedMem(4*sizeof(QUEUE));

    //Initializations of shared variables:
    *sec_ptr = 0;
    //memcpy(cars, importCars("../include/cars_x.txt"), sizeof(QUEUE));
    for(int i=0;i<4;i++){
        memcpy(car_queues[i], createQueue(MaxCar), sizeof(QUEUE));
    }

    //Initializations of semaphores:
    mutexTf = initSem();
    for(int i=0;i<4;i++){
        mutexCqs[i] = initSem();
        roads[i] = initSem();
    }
    
    if(fork() == 0){  //traffic lights process
        lights(sec_ptr, roads);
    }else {  //car processes
        pid_t pid;
        for(int i=0; i<(cars->size); i++){
            pid = fork();
            if(pid < 0){
                perror("Error occurred in function \"fork()\"!\n");
            }else if(pid == 0){  //[car process]*car_num
                car(sec_ptr, tf, car_queues, mutexTf, mutexCqs, roads);
            }
        }
        //parent process
        wait(0);
    }

    return 0;
}


void lights(double* sec_ptr, semaphore* roads){
    biOrient red_light = North_South;  //Initially, lights are red at North-South oriention; contrarily, lights are green at East-West.
    while(True){
        red_light = !red_light;  //Invert lights' color of two orientions
        if(red_light == North_South){    //lights red at North-South, block the North, South roads
            semop(road[North], P(), 1);
            semop(road[South], P(), 1);
            countDown(sec_ptr, 3, '-');  //a countdown timer in "minus" style
            semop(road[South], V(), 1);
            semop(road[North], V(), 1);
        }else {                          //lights red at East-West, block the East, West roads
            semop(road[East], P(), 1);
            semop(road[West], P(), 1);
            countDown(sec_ptr, 3, '+');  //a countdown timer in "plus" style
            semop(road[West], V(), 1);
            semop(road[East], V(), 1);
        }
    }
}

void car(double* sec_ptr, QUEUE* cars, QUEUE** cqs, semaphore mutexCars, semaphore* mutexCqs, semaphore* roads){
    //Take a car from mixed cars to one of the car queues as "me"
    semop(mutexCars, P(), 1);
    car me = deQueue(cars);
    semop(mutexCqs[me.from], P(), 1);
    enQueue(me, cqs[me.from]);
    semop(mutexCqs[me.from], V(), 1);
    semop(mutexCars, V(), 1);

    //Am I at the front of the queue?
    while(front(me.from).car_id != me.car_id);

    //Do I have enough time?
    if(me.from==North || me.from==South){                   //if north or south
        while((-(*sec_ptr) - me.est_time) <= SafeSeconds);
    }else{                                                  //if east or west
        while((*sec_ptr - me.est_time) <= SafeSeconds);
    }

    //Cross the road
    semop(road[me.from], P(), 1);
    sleep(me.est_time);
    semop(road[me.from], V(), 1);

    //Broadcast that I have passed the road
    printf("Car %d crossed the road with %lf secs.", me.car_id, me.est_time);

    //Dequeue me from the waiting queue
    semop(mutexCqs[me.from], P(), 1);
    deQueue(cqs[me.from]);
    semop(mutexCqs[me.from], V(), 1);

    //End process
    exit(0);
}
    
