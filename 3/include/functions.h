#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"definitions.h"

//Concerning I/O:
string assertThat(string prompt){
    printf("%s", prompt);
    exit(0);
}

void pause(char *prompt, int ascii){
    printf("%s\n", prompt);
    if(ascii == Null){
        getch();
    }else {
        while(getch() != ascii);
    }
}




//Concerning Array:
bool all(bool* array, int len){  //if all true
    bool is_all_true = True;
    for(int i=0;i<len;i++){
        is_all_true *= array[i];
    }
    return is_all_true;
}

bool append(int* array, int len, int element){
    for(int i=0;i<len;i++){
        if(array[i] == Null){
            array[i] = element;
            return True;
        }
    }
    return False;
}

void fill(int* array, int len, int value){
    for(int i=0;i<len;i++){
        array[i] = value;
    }
}

void printArray(int* array, int len){
    printf("[");
    for(int i=0;i<len;i++){
        if(i==len-1){
            printf("%d]\n", array[i]);
        }else {
            printf("%d, ", array[i]);
        }
    }
}




//Concerning String:
bool allInt(string str, int len){
    bool int_exists = False;
    for(int i=0;i<len;i++){
        if(str[i] == ' '){
            continue;
        }else if(str[i] >= '0' || str[i] <= '9'){
            int_exists = True;
        }else{
            return False;
        }
    }

    if(int_exists){
        return True;
    }else{
        return False;
    }
    
}

string upper(string str, int len){
    int distance = 'a' - 'A';
    string upper_str = (string) malloc((len+1)*sizeof(char));

    for(int i=0;i<len+1;i++){
        if(i == len + 1 || str[i] == '\0'){
            upper_str[i] = '\0';
            break;
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            upper_str[i] = str[i] - distance;
        }else {
            upper_str[i] = str[i];
        }
    }

    return upper_str;
}

string lower(string str, int len){
    int distance = 'a' - 'A';
    string lower_str = (string) malloc((len+1)*sizeof(char));

    for(int i=0;i<len+1;i++){
        if(i == len + 1 || str[i] == '\0'){
            lower_str[i] = '\0';
            break;
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
            lower_str[i] = str[i] + distance;
        }else {
            lower_str[i] = str[i];
        }
    }

    return lower_str;
}


//Concerning structs:
request createRequest(int p_num, int r_num){
    request rq = {
        p_num,
        (int*)malloc(r_num*sizeof(int))
    };

    return rq;
}

void destroyRequest(request rq){
    //TODO: destory a request var
};

sysStatus createSysStatus(int p_num, int r_num){
    sysStatus ss = {
        p_num,
        r_num,
        createM(p_num, r_num),
        createM(p_num, r_num),
        (int*)malloc(r_num*sizeof(int))
    };

    return ss;
}

void destroySysStatus(sysStatus* ss){
    destoryM(ss->allocation);
    destoryM(ss->need);
    free(ss->available);
};

void sysStatusCopy(sysStatus* ss1, sysStatus* ss2){  //copy the values from ss2 to ss1
    const int m = (ss1->p_num = ss2->p_num);
    const int n = (ss1->r_num = ss2->r_num);
    //assertThat("OK\n");
    mtxCpy(ss1->allocation, ss2->allocation, 'v');
    mtxCpy(ss1->need, ss2->need, 'v');
    assertThat("OK\n");
    memcpy(ss1->available, ss2->available, n*sizeof(int));
    assertThat("OK\n");
}






//Conerning The Algorithm:
request getRequest(sysStatus ss){
    //content: 1. Get a process's request from user's input; 
    //content: 2. If q/quit input, exit.
    const int m = ss.p_num;
    const int n = ss.r_num;
    int process;
    int seq[n];
    char input[32];
    char* p = input;
    int len;

    while(True){
        printf("(Banker's) ");
        scanf("%[^\n]", input);
        scanf("%c");
        
        if(strcmp(lower(input, strlen(input)), "q") == 0 || strcmp(lower(input, strlen(input)), "quit") == 0){
            exit(0);
        }else if(!allInt(input, strlen(input))){
            printf("Invalid input!\n");
        }else {
            sscanf(p, "%d%n", &process, &len);
            p += len + 1;

            if(process < 0 || process >= m){
                printf("Invalid process number!\n");
            }else {
                for(int i=0;i<n+1;i++){
                    if(i > n){
                        if(sscanf(p, "%d") != EOF){
                            printf("Requests exceeds resources!\n");
                        }
                    }else {
                        sscanf(p, "%d%n", seq + i, &len);
                        p += len + 1;
                    }
                }

                printArray(seq, n);
                request rq = createRequest(process, n);
                rq.p_num = process;
                memcpy(rq.sequence, seq, n*sizeof(int));

                return rq;
            }
        }
    }
    

}

sysStatus importStatus(path f_path){
    /*
    import sysStatus data from a txt file
    */
    
    FILE *data_f = fopen(f_path, "r");
    //import p_num, r_num
    int m;
    int n;
    fscanf(data_f, "%d %d", &m, &n);

    //create a sysStatus var for receival
    sysStatus ss = createSysStatus(m, n);
    
    //import allocation[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &ss.allocation[i][j]);
        }
    }

    //import need[m][n]
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            fscanf(data_f, "%d", &ss.need[i][j]);
        }
    }

    //import available[n]
    for(int i=0;i<n;i++){
        fscanf(data_f, "%d", ss.available + i);
    }

    //If file invalid
    fgetc(data_f);
    if(!feof(data_f)){
        fclose(data_f);
        assertThat("Invalid data file!");
        destroySysStatus(&ss);
    }else {  //Success
        fclose(data_f);
        return ss;
    }
}

void printStatus(sysStatus ss){
    /*
    content: print current p&r status
    */
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

request trialRequest(){
    request rq = createRequest(1, 3);
    int seq[3] = {0, 0, 0};
    memcpy(rq.sequence, seq, 3*sizeof(int));

    return rq;
}

sysStatus trialStatus(){
    //A trail sysStatus DS
    int alc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
        };
    int nd[5][3] = {
        {0, 0, 2},
        {2, 2, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
        };
    int ava[3] = {0, 0, 0};
    
    sysStatus ss = createSysStatus(5, 3);
    fillM(ss.allocation, 0);
    fillM(ss.need, 0);
    //assertThat("OK\n");
    mtxCpy(ss.allocation, (matrix)alc, 'v');
    mtxCpy(ss.need, (matrix)nd, 'v');
    memcpy(ss.available, ava, 3*sizeof(int));

    return ss;
}