#include"security_check.h"

signal bankers(sysStatus ss, request rq){
    /*
    Banker's Algorithm
    */
   sysStatus pre_allocate(sysStatus ss, request rq);

    //Definition of row number and column number for process-resource matrix
    const int m = ss.p_num;
    const int n = ss.r_num;
    const int process = rq.p_num;

    for(int i=0; i<n; i++){
        if(rq.sequence[i] > vofM(ss.need, process, i, n))
            return Error;
    }

    for(int i=0; i<n; i++){
        if(rq.sequence[i] > ss.available[i])
            return Wait;
    }

    sysStatus next_ss = pre_allocate(ss, rq);

    if(securityCheck(next_ss).check == False)
        return Wait;

    ss = next_ss;
    return Success;
}

sysStatus pre_allocate(sysStatus ss, request rq){
    sysStatus next_ss = ss;
    return next_ss;
}