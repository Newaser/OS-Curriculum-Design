#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include"queue.h"

#define True 1
#define False 0
#define Null -1
#define SafeSeconds 0.1
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

#endif
