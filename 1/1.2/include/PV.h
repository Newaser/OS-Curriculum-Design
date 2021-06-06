#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<string.h>

typedef struct sembuf atomic;

atomic* P(){  //P primitive
    //allocate memory to P
    atomic* P_op = (atomic*)malloc(sizeof(atomic));
    //initialize P
    atomic value = {
        0,
        1,
        SEM_UNDO
    };
    memcpy(P_op, &value, sizeof(atomic));
    return P_op;
}

atomic* V(){  //V primitive
    atomic* V_op = (atomic*)malloc(sizeof(atomic));
    atomic value = {
        0,
        -1,
        SEM_UNDO
    };
    memcpy(V_op, &value, sizeof(atomic));
    return V_op;
}
