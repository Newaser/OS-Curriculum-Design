#include<sys/wait.h>

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
    void lights_process(double* sec_ptr, semaphore* roads);  //traffic lights process
    void car_process(double* sec_ptr, QUEUE* cars, QUEUE** cqs, semaphore mutexCars, semaphore* mutexCqs, semaphore* roads);  // car process
    
    //Shared Memory Allocations:
    sec_ptr = (double*)sharedMem(sizeof(double));
    cars = (QUEUE*)sharedMem(sizeof(QUEUE));
    for(int i=0;i<4;i++){
        car_queues[i] = (QUEUE*)sharedMem(sizeof(QUEUE));
    }

    //Initializations of shared variables:
    *sec_ptr = 0;
    memcpy(cars, importCars("../include/cars_use.txt"), sizeof(QUEUE));
    for(int i=0;i<4;i++){
        memcpy(car_queues[i], createQueue(MaxCars), sizeof(QUEUE));
    }

    //Initializations of semaphores:
    mutexCars = initSem();
    for(int i=0;i<4;i++){
        mutexCqs[i] = initSem();
        roads[i] = initSem();
    }
    
    if(fork() == 0){  //traffic lights process
        lights_process(sec_ptr, roads);
    }else {  //car processes
        pid_t pid;
        for(int i=0; i<(cars->size); i++){
            pid = fork();
            if(pid < 0){
                perror("Error occurred in function \"fork()\"!\n");
            }else if(pid == 0){  //[car process]*car_num
                car_process(sec_ptr, cars, car_queues, mutexCars, mutexCqs, roads);
            }
        }
        //parent process
        wait(0);
    }

    return 0;
}


void lights_process(double* sec_ptr, semaphore* roads){
    biOrient red_light = North_South;  //Initially, lights are red at North-South oriention; contrarily, lights are green at East-West.
    while(True){
        red_light = !red_light;  //Invert lights' color of two orientions
        if(red_light == North_South){    //lights red at North-South, block the North, South roads
            semop(roads[North], P(), 1);
            semop(roads[South], P(), 1);
            printf("The lights turn red at North-South, green at East-West.\n");
            countDown(sec_ptr, LightTime, '-');  //a countdown timer in "minus" style
            semop(roads[South], V(), 1);
            semop(roads[North], V(), 1);
        }else {                          //lights red at East-West, block the East, West roads
            semop(roads[East], P(), 1);
            semop(roads[West], P(), 1);
            printf("The lights turn green at North-South, red at East-West.\n");
            countDown(sec_ptr, LightTime, '+');  //a countdown timer in "plus" style
            semop(roads[West], V(), 1);
            semop(roads[East], V(), 1);
        }
    }
}

void car_process(double* sec_ptr, QUEUE* cars, QUEUE** cqs, semaphore mutexCars, semaphore* mutexCqs, semaphore* roads){
    //Take a car from mixed cars to one of the car queues as "me"
    semop(mutexCars, P(), 1);
    car me = deQueue(cars);
    semop(mutexCqs[me.from], P(), 1);
    enQueue(me, cqs[me.from]);
    semop(mutexCqs[me.from], V(), 1);
    semop(mutexCars, V(), 1);

    //Am I at the front of the queue?
    while(front(cqs[me.from]).car_id != me.car_id);

    //Do I have enough time?
    if(me.from==North || me.from==South){                   //if north or south
        while((-(*sec_ptr) - me.est_time) <= SafeSeconds);
    }else{                                                  //if east or west
        while((*sec_ptr - me.est_time) <= SafeSeconds);
    }

    //Cross the road
    semop(roads[me.from], P(), 1);
    sleep(me.est_time);
    semop(roads[me.from], V(), 1);

    //Broadcast that I have passed the road
    printf("Car %d crossed the road with %lf secs.\n", me.car_id, me.est_time);

    //Dequeue me from the waiting queue
    semop(mutexCqs[me.from], P(), 1);
    deQueue(cqs[me.from]);
    semop(mutexCqs[me.from], V(), 1);

    //End process
    exit(0);
}
    
