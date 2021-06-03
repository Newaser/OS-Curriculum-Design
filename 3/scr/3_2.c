#include"..\\include\\security_check.h"

typedef char* path;

int main(){
    /*
    Security Algorithm: Receive a DS of process&resource status, and analyze the security of the system
    */
    sysStatus importStatus(path f_path);
    sysStatus importTrial(void);
    void securityAlarm(sysStatus ss, security sc);
    void printAllcation(sysStatus ss, security sc);

    sysStatus ss;
    //ss = importStatus("..\\DS\\p&r_status.txt");  //import data
    ss = importTrial();                           //import trial data
    security sc = security_check(ss);             //check the security: if secure, return the security sequence
    securityAlarm(ss, sc);                        //print the security status
    //printAllcation(ss, sc);                       //print the process of resource allocation
    pause("\nPress ESC to exit...", 27);
    
    return 0;
}

sysStatus importStatus(path f_path){
    //content: import data from a txt file
}

void securityAlarm(sysStatus ss, security sc){
    if(sc.check){
        printf("System is currently safe!\nThe security sequence is:\n");
        printArray(sc.sequence, ss.p_num);
    }else {
        printf("System is not safe!\n");
    }
}

void printAllcation(sysStatus ss, security sc){
    //content: print the process of resource allocation according to sc.sequence
}

sysStatus importTrial(){
    //A trail data set
    static int alc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
        };
    static int nd[5][3] = {
        {0, 0, 2},
        {2, 2, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
        };
    static int ava[3] = {0, 0, 0};
    
    sysStatus ss;
    ss.p_num = 5;
    ss.r_num = 3;
    ss.allocation = (int**)alc;
    ss.need = (int**)nd;
    ss.available = ava;

    return ss;
}