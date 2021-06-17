#include"bankers.h"

void printHelp();                               //print help information
bool importStatus(string, sysStatus*);          //from file path import sysStatus      
void printStatus(sysStatus);                    //print current p&r status
bool getRequest(string,sysStatus,request*);  //get request information from a string, constrained by sysStatus
void answerRequest(signal);                     //answer the request according to a signal
void securityAlarm(security);                   //alarm the security status
void printSafeAlloc(sysStatus);       //print the process of resource allocation according to security.sequence

void printHelp(){
    printf("Info of all commands are down below:\n");
    printf("\"help\"\n");
        printf("    Show help information.\n\n\n");
    printf("\"q/quit\"\n");
        printf("    Quit.\n\n\n");
    printf("\"import [file_path]\"\n");
        printf("    From [file_path] import processes and resources status data.\n\n\n");
    printf("\"status\"\n");
        printf("    Print current processes and resources status.\n\n\n");
    printf("\"request [request_seq]\"\n");
        printf("    Send a request to the system. In it, [request_seq] is formed as\n");
        printf("  \"[process num] [request0] [requset1] [request2]...\". \n");
        printf("    For example, \"0 1 2 3\" means process0 wants one resource1, two\n");
        printf("  resource2, and three resource3.\n\n\n");
    printf("\"security\"\n");
        printf("    Judge if the current status is safe. If it is, give a sequence\n");
        printf("  of resource allocation.\n\n\n");
    printf("\"SafeAlloc/SafeAllocation\"\n");
        printf("    Demostrate a possible process of resource allocation.\n\n\n");
}

bool importStatus(string str, sysStatus* ss){
    //read file path from a string
    char f_path[32] = "..\\DS\\";
    char file_name[16];
    char* read = str + strlen("import ");
    sscanf(read, "%s", file_name);
    strcat(f_path, file_name);
    strcat(f_path, ".txt");

    //Search if the file exists
    if(!findFile("..\\DS\\*.txt", file_name)){
        printf("Import failed. Data file not found.\n");
        return False;
    }

    FILE *data_f = fopen(f_path, "r");
    //import p_num, r_num
    int m;
    int n;
    fscanf(data_f, "%d %d", &m, &n);

    //create a new sysStatus for receival
    sysStatus new_ss = createSysStatus(m, n);
    
    //import allocation[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &new_ss.allocation[i][j]);
            if(feof(data_f)){
                fclose(data_f);
                destroySysStatus(new_ss);
                printf("Import failed. Invalid data file.\n");
                return False;
            }
        }
    }

    //import need[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &new_ss.need[i][j]);
            if(feof(data_f)){
                fclose(data_f);
                destroySysStatus(new_ss);
                printf("Import failed. Invalid data file.\n");
                return False;
            }
        }
    }

    //import available[n]
    for(int i=0;i<n;i++){
        fscanf(data_f, "%d", &new_ss.available[i]);
        if(i < n - 1 && feof(data_f)){
            fclose(data_f);
            destroySysStatus(new_ss);
            printf("Import failed. Invalid data file.\n");
            return False;
        }
    }


    int end;
    fscanf(data_f, "%d", &end);
    if(!feof(data_f)){  //If the file has extra content
        fclose(data_f);
        destroySysStatus(new_ss);
        printf("Import failed. Invalid data file.\n");
        return False;
    }else{  //Success
        fclose(data_f);
        alterSysStatus(ss, m, n);
        sysStatusCopy(ss, &new_ss);
        destroySysStatus(new_ss);
        printf("Data imported.\n");
        return True;
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
    printf("PID\t\tAllocation\t\t\t  Need\n");

    //print table content
    for(int i=0;i<m;i++){
        //print PID
        printf("%2d\t\t", i);

        //print Allocation
        printRow(ss.allocation, i, 'h');
        printf("\t\t\t");

        //print Need
        printRow(ss.need, i, 'h');
        printf("\n");
    }
    printf("\n");
}

bool getRequest(string str, sysStatus ss, request* rq){
    //read request sequence from a string
    string raw;
    char* read = str + strlen("request ");
    sscanf(read, "%[^\n]", raw);

    //if invalid form
    if(!strAllInt(raw)){
        printf("Invalid request form!\n");
        return False;
    }else{
        //Alter request size
        alterRequest(rq, ss.r_num);

        //read p_num
        int offset;
        sscanf(read, "%d%n", &rq->p_num, &offset);
        read += offset + 1;

        if(rq->p_num >= ss.p_num){  //if request's process num exceeds the max
            printf("Invalid process number!\n");
            return False;
        }else {
            for(int i=0;i<ss.r_num+1;i++){
                if(i == ss.r_num){
                    int eat;
                    if(sscanf(read, "%d", eat) != EOF){
                        printf("Too many requests of resources!\n");
                        return False;
                    }
                }else {
                    if(sscanf(read, "%d%n", &rq->sequence[i], &offset) == EOF){
                        printf("Too few requests of resources!\n");
                        return False;
                    }else{
                        read += offset + 1;
                    }
                }
            }
            return True;
        }
    }
}

void answerRequest(signal sgn){
    switch(sgn){
            case Error:
                printf("Invalid request!\n");
                break;
            case Wait:
                printf("This request should wait!\n");
                break;
            case Success:
                printf("Request accepted!\n");
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

void printSafeAlloc(sysStatus ss){
    //get security status
    security sc = securityCheck(ss);
    if(!sc.check){
        printf("Print safe Allocation failed. System is currently not safe!\n");
        return;
    }
    
    //define m, n, process
    const int m = ss.p_num;
    const int n = ss.r_num;
    
    int process;
    int* added_array;

    //create a sysStatus for demostrating
    sysStatus demo = createSysStatus(m, n);
    sysStatusCopy(&demo, &ss);

    //print table head
    printf("PID\t\tAvailable\t\t\tAllocation\t\t\t  Need\t\t\t  Available + Allocation\n");

    //print table content
    for(int i=0;i<m;i++){
        //get process number
        process = sc.sequence[i];

        //print PID
        printf("%2d\t\t", process);

        //print Available
        printArrayLine(demo.available, n);
        printf("\t\t\t");

        //print Allocation
        printRow(demo.allocation, process, 'h');
        printf("\t\t\t");

        //print Need
        printRow(demo.need, process, 'h');
        printf("\t\t\t");

        //print Available + Allocation
        added_array = addArray(demo.available, demo.allocation[process], n);
        printArrayLine(added_array, n);
        printf("\n");

        //next status
        fill(demo.allocation[process], n, 0);
        fill(demo.need[process], n, 0);
        arrayCopy(demo.available, added_array, n);

    }
    printf("\n");
}