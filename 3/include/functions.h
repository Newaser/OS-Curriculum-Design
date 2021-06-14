#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"definitions.h"

bool all(bool* array, int len){  //if all true
    bool is_all_true = True;
    for(int i=0;i<len;i++){
        is_all_true *= array[i];
    }
    return is_all_true;
}

bool allInt(string str, int len){
    for(int i=0;i<len;i++){
        if(str[i] < '0' || str[i] > '9'){
            return False;
        }
    }

    return True;
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

string assertThat(string prompt){
    printf("%s", prompt);
    exit(0);
}

string upper(string str, int len){
    int distance = 'a' - 'A';
    string upper_str = (string) malloc(len*sizeof(char));

    for(int i=0;i<len;i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            upper_str[i] = str[i] - distance;
        }else {
            upper_str[i] = str[i];
        }
    }

    return upper_str;
}

string lower(string str, int len){
    int distance = 'a' - 'A';
    string lower_str = (string) malloc(len*sizeof(char));

    for(int i=0;i<len;i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            lower_str[i] = str[i] + distance;
        }else {
            lower_str[i] = str[i];
        }
    }

    return lower_str;
}

int aofM(int** matrix, int row, int col, int row_len){  //address of matrix[row][col]
    return ((int*)matrix + row_len*row + col);
}

int vofM(int** matrix, int row, int col, int row_len){  //value of matrix[row][col]
    int value;
    value = *((int*)matrix + row_len*row + col);
    return value;
}

void fill(int* array, int len, int value){
    for(int i=0;i<len;i++){
        array[i] = value;
    }
}

void pause(char *prompt, int ascii){
    printf("%s\n", prompt);
    if(ascii == Null){
        getch();
    }else {
        while(getch() != ascii);
    }
}



request createRequest(int p_num, int r_num){
    request rq = {
        p_num,
        (int*)malloc(r_num*sizeof(int))
    };

    return rq;
}

request createSysStatus(int p_num, int r_num){
    sysStatus ss = {
        p_num,
        r_num,
        (int**)malloc(p_num*r_num*sizeof(int)),
        (int**)malloc(p_num*r_num*sizeof(int)),
        (int*)malloc(r_num*sizeof(int))
    };

    return ss;
}

request getRequest(sysStatus ss){
    //content: 1. Get a process's request from user's input; 
    //content: 2. If q/quit input, exit.
    int m = ss.p_num;
    int n = ss.r_num;
    int process;
    int seq[n];
    string input;

    printf("Please enter a process's request like \"[process num] [requset1] [request2] ...\":\n(Such as\"0 1 2 3\")\n");
    scanf("%s", input);

    if(!allInt(input, strlen(input))){
        assertThat("Invalid input!");
    }else {
        sscanf(input, "%d", &process);
        if(process < 0 || process >= m){
            assertThat("Invalid process number!");
        }else {
            for(int i=0;i<n+1;i++){
                if(i > n){
                    if(sscanf(input, "%d") != EOF){
                        assertThat("Requests exceeds resources!");
                    }
                }else {
                    sscanf(input, "%d", seq + i);
                }
            }

            request rq = createRequest(process, n);
            rq.p_num = process;
            memcpy(rq.sequence, seq, n*sizeof[int]);

            return rq;
        }
    }
    

}

sysStatus importStatus(path f_path){
    //content: import sysStatus data from a txt file
    string data;
    

    FILE *data_f = fopen(f_path, "r");
    fscanf(data_f, "%s", data);
    fclose(data_f);

    if(!allInt(data, strlen(data))){
        assertThat("Invalid data file!");
    }else {
        //import p_num, r_num
        int vof_m;
        int vof_n;
        sscanf(data, "%d %d", &vof_m, &vof_n);
        const int m = vof_m;
        const int n = vof_n;

        //define vars used for receival
        int alc[m][n];
        int nd[m][n];
        int ava[n];
        
        //import allocation[m][n]
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                sscanf(data, "%d", &alc[i][j]);
            }
        }

        //import need[m][n]
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                sscanf(data, "%d", &nd[i][j]);
            }
        }

        //import available[n]
        for(int i=0;i<n;i++){
            sscanf(data, "%d", &nd[i]);
        }

        if(sscanf(data, "%d") != EOF){
            assertThat("Invalid data file!");
        }else {
            sysStatus ss = createSysStatus(m, n);
            memcpy(ss.allocation, alc, m*n*sizeof(int));
            memcpy(ss.need, nd, m*n*sizeof(int));
            memcpy(ss.available, ava, n*sizeof(int));

            return ss;
        }

    }
    
}

void printStatus(sysStatus ss){
    //content: print current p&r status
    int m = ss.p_num;
    int n = ss.r_num;
    string table;
    string element;

    //add available array
    strcat(table, "Available Resoures:");
    for(int i=0;i<n;i++){
        itoa(ss.available[i], element, 10);
        strcat(table, element);
    }
    strcat(table, "\n\n");

    //add table head
    strcat(table, "PID\tAllocation\tNeed");

    //add table content
    for(int i=0;i<m;i++){
        //add PID
        for(int j=0;j<n;j++){
            //add Allocation, Need
        }
    }

    //print result
    printf("%s\n\n", table);
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
    memcpy(ss.allocation, alc, 15*sizeof(int));
    memcpy(ss.need, nd, 15*sizeof(int));
    memcpy(ss.available, ava, 3*sizeof(int));

    return ss;
}