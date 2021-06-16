#include"..\\include\\bankers_algorithm.h"

int main(){
    /*
    Input request stream: Avoid deadlock by Banker's Algorithm
    */
    //assertThat("OK\n");
    //sysStatus ss = importStatus(("..\\DS\\p&r_status_use.txt"));
    //assertThat("OK\n");
    sysStatus ss = trialStatus();
    assertThat("OK\n");
    //request rq = trialRequest();
    //assertThat("OK\n");
    printStatus(ss);  //print current p&r status of the system
    //assertThat("OK\n");
    printf("Please enter a process's request like \"[process num] [requset1] [request2] ...\" such as \"0 1 2 3\".\nEnter \"q/quit\" to exit.\n");
    while(True){  //a loop for inputing request stream
        //assertThat("OK\n");
        request rq = getRequest(ss);
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