#include<io.h>
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
string upper(string str){
    int len = strlen(str);

    int distance = 'a' - 'A';
    string upper_str = (string) malloc((len+1)*sizeof(char));

    for(int i=0;i<len+1;i++){
        if(i == len){
            upper_str[i] = '\0';
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            upper_str[i] = str[i] - distance;
        }else {
            upper_str[i] = str[i];
        }
    }

    return upper_str;
}

string lower(string str){
    int len = strlen(str);
    
    int distance = 'a' - 'A';
    string lower_str = (string) malloc((len+1)*sizeof(char));

    for(int i=0;i<len+1;i++){
        if(i == len){
            lower_str[i] = '\0';
        }else if(str[i] >= 'A' && str[i] <= 'Z'){
            lower_str[i] = str[i] + distance;
        }else {
            lower_str[i] = str[i];
        }
    }

    return lower_str;
}

bool strSimilar(string str1, string str2){
    if(strcmp(lower(str1), lower(str2)) == 0){
        return True;
    }else{
        return False;
    }
}

bool strnSimilar(string str1, string str2, int n){
    if(strncmp(lower(str1), lower(str2), n) == 0){
        return True;
    }else{
        return False;
    }
}

bool strAllInt(string str){  //If a string consists all of unsigned int except space
    int len = strlen(str);

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



//Concerning structs:
security* createSecurity(int p_num){
    security* sc = (security*)malloc(sizeof(security));
    sc->sequence = (int*)malloc(p_num*sizeof(int));

    return sc;
}

void destroySecurity(security* sc){
    if(sc != NULL){
        free(sc->sequence);
        free(sc);
    }
}

request createRequest(int r_num){
    request rq = {
        Null,
        (int*)malloc(r_num*sizeof(int))
    };

    return rq;
}

void destroyRequest(request rq){
    free(rq.sequence);
};

void alterRequest(request* rq, int r_num){
    destroyRequest(*rq);
    rq->sequence = (int*)malloc(r_num*sizeof(int));
}

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

void destroySysStatus(sysStatus ss){
    destroyM(ss.allocation);
    destroyM(ss.need);
    free(ss.available);
}

void alterSysStatus(sysStatus* ss, int p_num, int r_num){
    destroySysStatus(*ss);
    if(p_num != Null){
        ss->p_num = p_num;
    }
    if(r_num != Null){
        ss->r_num = r_num;
    }

    ss->allocation = createM(p_num, r_num);
    ss->need = createM(p_num, r_num);
    ss->available = (int*)malloc(r_num*sizeof(int));

}

bool sysStatusCopy(sysStatus* ss1, sysStatus* ss2){  //copy the values from ss2 to ss1
    if (ss1->p_num != ss2->p_num || ss1->r_num != ss2->r_num){
        return False;
    }else{
        const int m = ss1->p_num;
        const int n = ss1->r_num;
        //assertThat("OK\n");
        mtxCpy(ss1->allocation, ss2->allocation, 'v');
        mtxCpy(ss1->need, ss2->need, 'v');
        memcpy(ss1->available, ss2->available, n*sizeof(int));

        return True;
    }
}



//Concerning file:
bool findFile(path f_path, string dest_name){
    long HANDLE;
    struct _finddata_t f_data;
    if((HANDLE = _findfirst(f_path, &f_data)) == -1L){
        _findclose(HANDLE);
        return False;
    }else{
        do{
            if(strnSimilar(f_data.name, dest_name, strlen(f_data.name)-strlen(".txt"))){
                _findclose(HANDLE);
                return True;
            }
        }
        while(_findnext(HANDLE, &f_data) == 0);
        _findclose(HANDLE);
        return False;
    }
}