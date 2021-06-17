#include"..\\include\\security_check.h"

int main(){
    /*
    Security Algorithm: Receive a DS of process&resource status, and analyze the security of the system
    */
    void securityAlarm(sysStatus ss, security sc);
    void printAllocation(sysStatus ss, security sc);

    sysStatus ss;
    //ss = importStatus("..\\DS\\p&r_status_use.txt");   //import p&r status from external file
    ss = trialStatus();                              //import trial data
    printStatus(ss);                                 //print current p&r status of the system
    security sc = securityCheck(ss);                 //check the security: if secure, return the security sequence
    securityAlarm(ss, sc);                           //print if secure
    //printAllocation(ss, sc);                         //print a feasible approach of resource allocation
    pause("\nPress ESC to exit...", 27);
    
    return 0;
}



void printAllocation(sysStatus ss, security sc){
    //content: print the process of resource allocation according to sc.sequence
}