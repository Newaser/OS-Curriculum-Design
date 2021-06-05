#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"definitions.h"

char* assertThat(char* prompt){
    printf("%s", prompt);
    exit(0);
}

traffic* importTraffic(path f_path){
    //content: import traffic data from a txt file
}

void pause(char *prompt, int ascii){
    printf("%s\n", prompt);
    if(ascii == Null){
        getch();
    }else {
        while(getch() != ascii);
    }
}