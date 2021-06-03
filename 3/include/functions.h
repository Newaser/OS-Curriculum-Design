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

bool append(int* array, int len, int element){
    for(int i=0;i<len;i++){
        if(array[i] == Null){
            array[i] = element;
            return True;
        }
    }
    return False;
}

char* assertThat(char* prompt){
    printf("%s", prompt);
    exit(0);
}

void fill(int* array, int len, int value){
    for(int i=0;i<len;i++){
        array[i] = value;
    }
}

request getRequest(){
    //content: 1. Get a process's request from user's input; 
    //content: 2. If key ESC pressed, exit.
}

sysStatus importStatus(path f_path){
    //content: import sysStatus data from a txt file
}

void pause(char *prompt, int ascii){
    printf("%s\n", prompt);
    if(ascii == Null){
        getch();
    }else {
        while(getch() != ascii);
    }
}

void printStatus(sysStatus ss){
    //content: print current p&r status
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
    request rq = {
        1,
        (int*)malloc(3*sizeof(int))
    };
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
    
    sysStatus ss = {
        5,
        3,
        (int**)malloc(15*sizeof(int)),
        (int**)malloc(15*sizeof(int)),
        (int*)malloc(3*sizeof(int))
    };
    memcpy(ss.allocation, alc, 15*sizeof(int));
    memcpy(ss.need, nd, 15*sizeof(int));
    memcpy(ss.available, ava, 3*sizeof(int));

    return ss;
}

int vofM(int** matrix, int row, int col, int len){  //return the value of matrix[row][col]
    int value;
    value = *((int*)matrix + len*row + col);
    return value;
}