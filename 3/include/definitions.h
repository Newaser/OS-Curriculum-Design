#define True 1
#define False 0
#define Null -1
typedef int bool;

typedef struct sysStatus{  //system status concerning processes and resources
    int p_num;  //amount of processes
    int r_num;  //amount of resources

    //allocation, need matrixes of resources
    int** allocation;
    int** need;

    int* available;  //available resources vector
} sysStatus;

typedef struct security{
    bool check;
    int* sequence;
} security;