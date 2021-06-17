#include"..\\include\\commands.h"

int main(){
    /*
    Input request stream: Avoid deadlock by Banker's Algorithm
    */
    void answerRequest(signal bks);
    string getCommand();

    sysStatus ss = importStatus(("..\\DS\\p&r_status_use.txt"));  //import p&r status from external file
    security sc = createSecurity(ss.p_num);
    request rq = createRequest(ss.r_num);
    string command;

    printf("Please enter a process's request like \"[process num] [requset1] [request2] ...\" such as \"0 1 2 3\".\nEnter \"q/quit\" to exit.\n");
    while(True){  //command receiving loop
        command = getCommand();
        if(strSimilar(command, "q") || strSimilar(command, "quit")){
            exit(0);
        }else if(strSimilar(command, "help")){
            printHelp();
        }else if(strnSimilar(command, "import", strlen("import"))){
            importStatus(command, &ss);
        }else if(strSimilar(command, "status")){
            printStatus(ss);
        }else if(strnSimilar(command, "request", strlen("request"))){
            getRequest(command, &rq);
            answerRequest(bankers(ss, rq));
        }else if(strSimilar(command, "security")){
            securityAlarm(ss);
        }else if(strSimilar(command, "SafeAlloc") || strSimilar(command, "SafeAllocation")){
            printSafeAlloc(ss, sc);
        }else{
            printf("Invalid command!\n");
        }
    }

    return 0;
}



string getCommand(){
    string command = (string)mallc(32*sizeof(char));
    printf("(Banker's) ");
    scanf("%[^\n]", command);
    scanf("%c");

    return command;
}


