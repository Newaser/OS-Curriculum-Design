#include"matrix.h"

#define True 1
#define False 0
#define Null -1
typedef int bool;
typedef char* path;
typedef char* string;

typedef enum signal{
    Error=-1,
    Wait,
    Success
} signal;

typedef struct security{
    bool check;
    int* sequence;
} security;

typedef struct request{
    int p_num;
    int* sequence;
} request;

typedef struct sysStatus{  //system status concerning processes and resources
    int p_num;  //amount of processes
    int r_num;  //amount of resources

    //allocation, need matrix of resources
    matrix allocation;
    matrix need;

    int* available;  //available resources vector
} sysStatus;