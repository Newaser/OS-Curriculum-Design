#include"queue.h"

#define True 1
#define False 0
#define Null -1
#define SleepGranu 0.1
#define SafeSeconds 0.3
#define MaxCar 5
typedef int bool;
typedef int semaphore;
typedef char* path;

typedef enum quaOrient{  //cars' and roads' oriention type(quaternary): North, South, Eest, West
    North, South, East, West
} quaOrient;

typedef enum biOrient{  //light's oriention type(binary): North-South, Eest-West
    North_South,
    East_West
} biOrient;

typedef struct car{
    int car_id;
    quaOrient from;
    double est_time;  //estimated time to pass the crossing
} car, elementType;

typedef struct QUEUE
{
    int capacity;        //max amount of elements
    int front;           //cursor of the front element
    int rear;            //cursor of the rear element
    int size;            //the amount of elements
    elementType *array;  //the array of elements
} QUEUE;

int isEmpty(QUEUE *q);                          //if empty
int isFull(QUEUE *q);                           //if full
QUEUE *createQueue(int maxElements);            //create a queue
void disposeQueue(QUEUE *q);                    //dispose a queue
void makeEmpty(QUEUE *q);                       //init or empty a queue
void enQueue(elementType element, QUEUE *q);    //enqueue a element 
elementType front(QUEUE *q);                    //return the front element
elementType deQueue(QUEUE *q);                  //return the front element and dequeue it
