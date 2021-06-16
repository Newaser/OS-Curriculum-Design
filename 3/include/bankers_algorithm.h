#include"security_check.h"

signal bankers(sysStatus ss, request rq){
    /*
    Banker's Algorithm
    */
   sysStatus pre_allocate(sysStatus ss, request rq, int m, int n, int process);

    //Definition of row number and column number for process-resource matrix
    const int m = ss.p_num;
    const int n = ss.r_num;
    const int process = rq.p_num;

    //If request > need, error
    for(int i=0; i<n; i++){
        if(rq.sequence[i] > (ss.need, process, i, n))
            return Error;
    }

    //If request > available, wait
    for(int i=0; i<n; i++){
        if(rq.sequence[i] > ss.available[i])
            return Wait;
    }

    //pre-allocate resources
    sysStatus next_ss = pre_allocate(ss, rq, m, n, process);
    printStatus(next_ss);

    //If system not safe, wait; if safe, success
    if(securityCheck(next_ss).check == False){
        return Wait;
    }else {
        ss = next_ss;
        return Success;
    }
}

sysStatus pre_allocate(sysStatus ss, request rq, int m, int n, int process){
    //content: allocate the requested resources from system to process
    sysStatus next_ss = createSysStatus(m, n);
    sysStatusCopy(&next_ss, &ss);
    assertThat("OK\n");

    for(int i=0;i<ss.r_num;i++){
        next_ss.available[i] = ss.available[i] - rq.sequence[i];
        printf("X: %d\n", ss.allocation[process][i]);
        printf("Y: %d\n", ss.need[process][i]);
        next_ss.allocation[process][i] = ss.allocation[process][i] + rq.sequence[i];
        next_ss.need[process][i] = ss.need[process][i] - rq.sequence[i];
    }
    
    return next_ss;
}