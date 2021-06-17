#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef int** matrix;

matrix createM(int row, int col){  //create a matrix
    matrix mtx = (matrix)malloc(row*sizeof(int*));
    for(int i=0;i<row;i++){
        mtx[i] = (int*)malloc(col*sizeof(int));
    }
    return mtx;
}

void destroyM(matrix mtx){
    if(mtx != NULL){
        int row = _msize(mtx)/sizeof(int*);
        int col = _msize(*mtx)/sizeof(int);

        for(int i=0;i<row;i++){
        free(mtx[i]);
        }
        free(mtx);
    }
}

/*
Element: mtx[m][n]
*/

void mtxCpy(matrix dest, matrix origin, char mode){
    int row = _msize(dest)/sizeof(int*);
    int col = _msize(*dest)/sizeof(int);

    int o_row = _msize(dest)/sizeof(int*);
    int o_col = _msize(*dest)/sizeof(int);

    if(row != o_row || col != o_col){
        printf("Function \"MtxCpy\" failed. Row numbers or col numbers do not match.\n");
        exit(0);
    }else {
        if(mode == 'v'){  //Value Mode
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    dest[i][j] = origin[i][j];
                }
            }

        }else if(mode == 'm'){  //Memory Mode

            memcpy(dest, origin, row*sizeof(int*));
            for(int i=0;i<row;i++){
                memcpy(dest[i], origin[i], col*sizeof(int));
            }

        }else{
            printf("Function \"MtxCpy\" failed. Invalid mode type.\n");
            exit(0);
        }
        
    }
}

void fillM(matrix mtx, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            mtx[i][j] = value;
            printf("FILL: %d\n", mtx[i][j]);
        }
    }
    
}

void fillRow(matrix mtx, int the_row, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(the_row > row){
        printf("Function \"fillRow\" failed. The row exceeds max row.\n");
        exit(0);
    }else {
        for(int i=0;i<col;i++){
            mtx[the_row][i] = value;
        }
    }
}

void fillCol(matrix mtx, int the_col, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(the_col > col){
        printf("Function \"fillCol\" failed. The col exceeds max col.\n");
        exit(0);
    }else {
        for(int i=0;i<row;i++){
            mtx[i][the_col] = value;
        }
    }
}

BOOL allM(matrix mtx, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(mtx[i][j] != value){
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL allRow(matrix mtx, int the_row, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(the_row > row){
        printf("Function \"fillCol\" failed. The col exceeds max col.\n");
        exit(0);
    }else {
        for(int i=0;i<col;i++){
            if(mtx[the_row][i] != value){
                return FALSE;
            }
        }
        return TRUE;
    }
}

BOOL allCol(matrix mtx, int the_col, int value){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(the_col > row){
        printf("Function \"allCol\" failed. The col exceeds max col.\n");
        exit(0);
    }else {
        for(int i=0;i<col;i++){
            if(mtx[i][the_col] != value){
                return FALSE;
            }
        }
        return TRUE;
    }
}

void printM(matrix mtx, char mode){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(mode == ' '){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(j == col - 1){
                    printf("%d\n", mtx[i][j]);
                }else{
                    printf("%d ", mtx[i][j]);
                }
            }
        }
    }else if(mode == 'T'){
        for(int j=0;j<col;j++){
            for(int i=0;i<row;i++){
                if(j == col - 1){
                    printf("%d\n", mtx[i][j]);
                }else{
                    printf("%d ", mtx[i][j]);
                }
            }
        }
    }else{
        printf("Function \"printM\" failed. Invalid mode type.\n");
        exit(0);
    }
        
}

void printRow(matrix mtx, int the_row, char mode){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(mode == 'h'){
        for(int i=0;i<col;i++){
            if(i == col - 1){
                printf("%d", mtx[the_row][i]);
            }else{
                printf("%d ", mtx[the_row][i]);
            }
        }
    }else if(mode == 'v'){
        for(int i=0;i<col;i++){
            printf("%d\n", mtx[the_row][i]);
        }
    }else{
        printf("Function \"printRow\" failed. Invalid mode type.\n");
        exit(0);
    }
}

void printCol(matrix mtx, int the_col, char mode){
    int row = _msize(mtx)/sizeof(int*);
    int col = _msize(*mtx)/sizeof(int);

    if(mode == 'h'){
        for(int i=0;i<col;i++){
            if(i == col - 1){
                printf("%d", mtx[i][the_col]);
            }else{
                printf("%d ", mtx[i][the_col]);
            }
        }
    }else if(mode == 'v'){
        for(int i=0;i<col;i++){
            printf("%d\n", mtx[i][the_col]);
        }
    }else{
        printf("Function \"printCol\" failed. Invalid mode type.\n");
        exit(0);
    }
}