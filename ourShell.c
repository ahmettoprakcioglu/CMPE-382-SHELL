/*
CMPE_382 Section 01 Project 1
Members:
Tanercan Altuntas
Ahmet Kaan Toprakcioglu
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>


void* functionThread(void* arg){ // Take the arg from parameter then send the system function.
    
    system(arg);
    pthread_exit(NULL);
}
FILE* batchfile;

int main(int argc, char *argv[]){

char input[512];
char* inputptr;
inputptr=input;


if(argc<2){
    // control command line input, if it is true, the program run with interactive mode.
    printf("ahmet@tanercan:>");
    fgets(inputptr,512,stdin);
}else{
    // else statement intialize the batchfile. If fopen can not find the value what is batch file. Send error message then, the program continue with interactive mode.
    batchfile= fopen(argv[1],"r");
    if(!batchfile){
        printf("%s\n",strerror(errno));
        argc--;
        printf("ahmet@tanercan:>");
        fgets(inputptr,512,stdin);
    }else{
        fgets(input,512,batchfile);
    }
}

    int index;
    int control;
    int controlQuit;
while(strcmp(inputptr,"quit\n")!=0){
    
    index=0;
    control=1;
    controlQuit=0;
    while(input[index]!='\n'){
        if(input[index]==';'){
            control=0;
            break;
        }
        index++;
    }
    if(control){
        //this checks whether the statement input has a ";" character in it.
        if(strstr(input,"|")){
            char* tokenPipe = strtok(input, "|");
            while(tokenPipe!=NULL){
                system(tokenPipe);
                tokenPipe=strtok(NULL,"|");
            }
        }else{
            // else condition, the input is a single command to send it directly system function.
            system(input);
        }
       
    }else{
        //program run here. If input include ";" or ";|" characters.
            pthread_t newthread;
            if(strstr(input,"|")){
                /*
                This declaration checks if the input contains the pipe character. Separates inputs with a pipe character.
                Then it separates the inputs separated by the pipe character with semicolon characters if they contain semicolon characters and sends them to the thread function.
                */
                char* token2 = strtok(input, "|");
                while(token2!=NULL){
                    
                    if(strstr(token2,";")){
                        pthread_t newthread2;
                        char* seperate;
                        while((seperate=strsep(&token2,";"))!=NULL){
                            if(strstr(seperate,"quit")){
                                controlQuit=1;
                            }
                            else{
                                pthread_create(&newthread2, NULL, functionThread, (void *)seperate);
                            }
                        }
                    }else{
                        if(strstr(token2,"quit")){
                            controlQuit=1;
                        }else{
                            system(token2);
                        }
                        
                    }
                    token2=strtok(NULL,"|");
                }
            }else{
                /*
                In this condition, the input contains only semicolon characters with input. Thus, it separates it with semicolon character and sends it to the thread function.
                */
                char* token1 = strtok(input, ";");
                while (token1 != NULL) {
                    if(strstr(token1,"quit")){
                        controlQuit=1;
                    }else{
                        pthread_create(&newthread,NULL,functionThread,(void *)token1); 
                    }
                    token1 = strtok(NULL, ";");
                }
            }
            
           sleep(1);

    }
    if(controlQuit){
        /*
        If this statement contains the word "quit" in any part of the input, it is not sent to the thread function.
        First of all, the work must be done in the thread function.
        */
        strcpy(inputptr,"quit\n");
    }else{
        //else statement define inputs according to some conditions.
        if(argc<2){
            //the user just ran the ourShellOutput file.
            printf("ahmet@tanercan:>");
            fgets(inputptr,512,stdin);
        }else{
            
                if(batchfile!=NULL){
                    //read lines from the batch file end of theese line, the file close.
                    if((fgets(input,512,batchfile))==NULL){
                        fclose(batchfile);
                        batchfile=NULL;
                        
                    }
                }
                
                if(batchfile==NULL){
                    //If the batch file is closed, the program continues as interactive mode.
                    printf("ahmet@tanercan:>");
                    fgets(inputptr,512,stdin);
                    
                }
            
        }
        
    } 
    
}

return 0;
}
