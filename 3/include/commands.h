#include"bankers.h"

void printHelp();                               //print help information
void importStatus(string, sysStatus*);          //from file path import sysStatus      
void printStatus(sysStatus);                    //print current p&r status
void getRequest(string,sysStatus,request*);  //get request information from a string, constrained by sysStatus
void answerRequest(signal);                     //answer the request according to a signal
void securityAlarm(security);                   //alarm the security status
void printSafeAlloc(sysStatus, security);       //print the process of resource allocation according to security.sequence

void printHelp(){
    printf("Info of all commands are down below:\n");
    printf("\"help\"\n");
        printf("\tShow help information.\n\n");
    printf("\"q/quit\"\n");
        printf("\tQuit.\n\n");
    printf("\"import [file_path]\"");
        printf("\tFrom [file_path] import processes and resources status data.\n\n");
    printf("\"status\"\n");
        printf("\tPrint current processes and resources status.\n\n");
    printf("\"request [request_seq]\"\n")
        printf("\tSend a request to the system.\n");
        printf("\tIn it, [request_seq] is formed as \"[process num] [request0] [requset1] [request2]...\".\n");
        printf("\tFor example, \"0 1 2 3\" means process0 wants one resource1, two resource2, and three resource3.\n\n");
    printf("\"security\"\n");
        printf("\tJudge if the current status is safe. If it is, give a sequence of resource allocation.\n\n");
    printf("\"SafeAlloc/SafeAllocation\"\n")
        printf("\tDemostrate a possible process of resource allocation.\n");
}

void importStatus(string str, sysStatus* ss){
    //read file path from a string
    path f_path = "..\\DS\\";
    string file_name;
    char* read = str + strlen("request") + 1;
    sscanf(read, "%s", file_name);
    strcat(f_path, file_name);
    strcat(f_path, ".txt");


    FILE *data_f = fopen(f_path, "r");
    //import p_num, r_num
    int m;
    int n;
    fscanf(data_f, "%d %d", &m, &n);
    
    //import allocation[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &ss->allocation[i][j]);
        }
    }

    //import need[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &ss->need[i][j]);
        }
    }

    //import available[n]
    for(int i=0;i<n;i++){
        fscanf(data_f, "%d", &ss->available[i]);
    }

    //If file invalid
    fscanf(data_f, "%d");
    if(!feof(data_f)){
        fclose(data_f);
        destroySysStatus(&ss);
        assertThat("Import failed. Invalid data file.\n");
    }else {  //Success
        fclose(data_f);
        return ss;
    }
}

void printStatus(sysStatus ss){
    //define m, n
    const int m = ss.p_num;
    const int n = ss.r_num;

    //print available array
    printf("Available Resoures: ");
    printArray(ss.available, n);
    printf("\n");

    //print table head
    printf("PID\tAllocation\tNeed\n");

    //print table content
    for(int i=0;i<m;i++){
        //print PID
        printf("%d\t", i);

        //print Allocation
        printRow(ss.allocation, i, 'h');
        printf("\t\t");

        //print Need
        printRow(ss.need, i, 'h');
        printf("\n");
    }
    printf("\n");
}

void getRequest(string str, sysStatus ss, request* rq){
    //read request sequence from a string
    string raw;
    char* read = str + strlen("request") + 1;
    sscanf(read, "%[^\n]", raw);

    //if invalid form
    if(!strAllInt(raw)){
        printf("Invalid request form!\n");
        return;
    }else{
        //read p_num
        int offset;
        sscanf(read, "%d%n", &rq->p_num, &offset);
        read += offset + 1;

        if(rq->p_num >= ss.p_num){  //if request's process num exceeds the max
            printf("Invalid process number!\n");
            return;
        }else {
            for(int i=0;i<ss.r_num+1;i++){
                if(i > ss.r_num){
                    if(sscanf(read, "%d") != EOF){
                        printf("Too many requests of resources!\n");
                        return;
                    }
                }else {
                    if(sscanf(read, "%d%n", &rq->sequence[i], &offset) == EOF){
                        printf("Too few requests of resources!\n");
                        return;
                    }else{
                        read += offset + 1;
                    }
                }
            }
        }
    }
}

void answerRequest(signal sgn){
    switch(sgn){
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

void securityAlarm(security sc){
    int seq_len = _msize(sc.sequence)/sizeof(int);

    if(sc.check){
        printf("System is currently safe!\nThe security sequence is: ");
        printArray(sc.sequence, seq_len);
    }else {
        printf("System is not safe!\n");
    }
}

void printSafeAlloc(sysStatus ss, security sc){
    /*
    TODO: Print safe allocation according to sc.sequence
    */
}