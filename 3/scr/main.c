#include"..\\include\\commands.h"

int main(){
    /*
    Input request stream: Avoid deadlock by Banker's Algorithm
    */
    string getCommand();

    sysStatus ss = createSysStatus(1, 1);
    bool have_status = False;
    request rq = createRequest(1);
    string command;

    printf("Enter \"help\" for more information.\n");
    while(True){  //command receiving loop
        command = getCommand();

        if(strSimilar(command, "q") || strSimilar(command, "quit")){
            exit(0);
        }else if(strSimilar(command, "help")){
            printHelp();
        }else if(strSimilar(command, "lsData") || strSimilar(command, "listData")){
            if(!listData()){
                printf("No data. Please add at least one.");
            }
        }else if(strnSimilar(command, "import ", strlen("import "))){
            if(importStatus(command, &ss)){
                have_status = True;
            }
        }else if(strSimilar(command, "status")){
            if(have_status){
                printStatus(ss);
            }else{
                printf("No processes and resources status data. Please import it first.\n");
            }
        }else if(strnSimilar(command, "request ", strlen("request "))){
            if(have_status){
                if(!getRequest(command, ss, &rq)){
                    continue;
                }
                answerRequest(bankers(&ss, rq));
            }else{
                printf("No processes and resources status data. Please import it first.\n");
            }
        }else if(strSimilar(command, "security")){
            if(have_status){
                securityAlarm(securityCheck(ss));
            }else{
                printf("No processes and resources status data. Please import it first.\n");
            }
        }else if(strSimilar(command, "SafeAlloc") || strSimilar(command, "SafeAllocation")){
            if(have_status){
                printSafeAlloc(ss);
            }else{
                printf("No processes and resources status data. Please import it first.\n");
            }
        }else{
            printf("Invalid command!\n");
        }
    }

    return 0;
}



string getCommand(){
    int eat;
    string command = (string)malloc(32*sizeof(char));
    memset(command, '\0', 32);
    
    printf("(Banker's) ");
    while(True){
        scanf("%[^\n]", command);
        scanf("%c", &eat);
        if(command[0] == '\0'){  //If the command is null (which means the user pressed "enter" directly)
            moveCursor(strlen("(Banker's) "), -1, 'r');
        }else{
            break;
        }
    }

    return command;
}


