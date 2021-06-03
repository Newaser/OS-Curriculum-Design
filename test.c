#include<stdio.h>
#include<stdlib.h>

void matrixTest();
void arrayTest();
void boolTest();

int main(){
    //matrixTest();
    //arrayTest();
    boolTest();

    return 0;
}

void matrixTest(){
    const int data[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}
    };
    
    const int (*p)[4] = data;
    //const int *q = data;
    printf("%d\n", *(*p+3));
    //printf("%d\n", *(q+1));
    //system("pause");

}

void arrayTest(){
    int array[5];
    array[0] = 0;
    //for(int i=0;i<6;i++)
    //    printf("%d", array[i]);
    printf("%d", array[7]);
}

void boolTest(){
    //printf("%d", 1&&1);
    int i = 1;
    i *= 0;
    printf("%d", i);
}