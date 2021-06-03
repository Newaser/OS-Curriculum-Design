#include<stdarg.h>
#include"functions.h"

typedef struct sysStatus{
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

security security_check(sysStatus ss){
    /*
    Security Check Algorithm
    */
    void pre_run(security sc, int m, int n, int process, sysStatus ss, int* work, int* finish);
    security final_check(security sc, int m, int* finish);

    //Definition of row number and column number for process-resource matrix
    const int m = ss.p_num;
    const int n = ss.r_num;

    security sc = {  //return value type
        False,
        (int*)malloc(m*sizeof(int))  //*sequence = (int*)*m
    };

    int work[n];  //temprarily available resources
    bool finish[m];  //processes that finished running

    //if runnable, which process, which resource
    bool runnable;
    int process;
    int resource;
    
    //Work resoures equals to available ones initially,
    //and NO process finished initially
    fill(sc.sequence, m, Null);
    memcpy(work, ss.available, n*sizeof(int));  //work = available[:]
    fill(finish, m, False);  //finish = [False]*m

    while(True){  //runnable process searching loop

        //A walking-through aimed to find a runnable process
        for(process=0;process<m;process++){
            runnable = True;  //Suppose it is runnable initially
            for(resource=0;resource<n;resource++){  //Judge if the process runnable
                runnable *= (!finish[process]) && (vofM(ss.need,process,resource,n)<=work[resource]);
            }
            //If runnable, break out
            if(runnable) break;
        }

        //If a runnable process found, pre-run it, then continue looping;
        //if not, check the security.
        if(runnable){
            pre_run(sc, m, n, process,ss, work, finish);
        } else{
            return final_check(sc, m, finish);
        }
    }
}


void pre_run(security sc, int m, int n, int process,sysStatus ss, int* work, int* finish){
    for(int resource=0;resource<n;resource++){
        work[resource] += vofM(ss.allocation,process,resource,n);
    }
    finish[process] = True;
    append(sc.sequence, m, process);
}

security final_check(security sc, int m, int* finish){
    if(all(finish, m)){  //if all finished, safe
        sc.check = True;
        return sc;
    }else {  //if not, unsafe, and ease the memory
        sc.check = False;
        free(sc.sequence);
        sc.sequence = NULL;
        return sc;
    }
}