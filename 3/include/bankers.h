#include"security_check.h"

signal bankers(sysStatus* ss, request rq){
    /*
    Banker's Algorithm
    */
   sysStatus pre_allocate(sysStatus ss, request rq);

    //Definition of row number and column number for process-resource matrix
    const int m = ss->p_num;
    const int n = ss->r_num;
    const int process = rq.p_num;

    //If request > need, error
    for(int i=0; i<n; i++){
        if(rq.sequence[i] > ss->need[process][i])
            return Error;
    }

    //If request > available, wait
    for(int i=0; i<n; i++){
        if(rq.sequence[i] > ss->available[i])
            return Wait;
    }

    //pre-allocate resources
    sysStatus next_ss = pre_allocate(*ss, rq);

    //If system not safe, wait; if safe, success
    if(securityCheck(next_ss).check == False){
        destroySysStatus(next_ss);
        return Wait;
    }else {
        sysStatusCopy(ss, &next_ss);
        destroySysStatus(next_ss);
        return Success;
    }
}

sysStatus pre_allocate(sysStatus ss, request rq){
    //content: allocate the requested resources from system to process
    const int m = ss.p_num;
    const int n = ss.r_num;
    const int process = rq.p_num;

    sysStatus next_ss = createSysStatus(m, n);
    sysStatusCopy(&next_ss, &ss);

    for(int i=0;i<ss.r_num;i++){
        next_ss.available[i] = ss.available[i] - rq.sequence[i];
        next_ss.allocation[process][i] = ss.allocation[process][i] + rq.sequence[i];
        next_ss.need[process][i] = ss.need[process][i] - rq.sequence[i];
    }
    
    return next_ss;
}