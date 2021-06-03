#include"..\\include\\bankers_algorithm.h"

int main(){
    /*
    Input request stream: Avoid deadlock by Banker's Algorithm
    */
    //sysStatus ss = importStatus(("..\\DS\\p&r_status_x.txt"));
    sysStatus ss = trialStatus();
    request rq = trialRequest();
    printStatus(ss);  //print current p&r status of the system

    while(True){  //a loop for inputing request stream
        //request rq = getRequest();
        switch(bankers(ss, rq)){
            case Error:
                printf("Invalid request!\n");
                break;
            case Wait:
                printf("Proccess %d's request should wait!\n", rq.p_num);
                break;
            case Success:
                printf("Request accepted!\n");
                printStatus(ss);
                break;
            default:
                assertThat("Error has occurred in function \"bankers\"!\n");
        }
    }

    return 0;
}