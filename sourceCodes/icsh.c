/* ICCS227: Project 1: icsh
 * Name: Zwe Min Thant
 * StudentID: 6581183
 */

#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../headers/Toknizer.h"
#include "../headers/MileStone1.h"
#include "../headers/icsh.h"



int loop; 
int exit_code;

int main(int argc, char* argv[]) {

    char* input; 
    char* cmd;
    loop = 1; 
    char* pastcmd = malloc(225 * sizeof(char));

    //MileStone 2
    if(argc > 1){

        FILE* fp = fopen(argv[1], "r");

        if(fp == NULL){
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }

        input = malloc(225 * sizeof(char));

        while(fgets(input, 225, fp) != NULL){
            if(isspace(input[0]) || input[0] == '#' ) {
                continue;
            }
            input[strcspn(input, "\n")] = 0;
            char* cmd = commandChecker(input);
            commandExe(input, cmd, pastcmd);
            free(cmd);
        }

        fclose(fp);
        free(input);
        free(pastcmd);
        return 0;
    }

    else{
        while(loop != 0){

            input = toknizer();
            cmd = commandChecker(input); 
            commandExe(input, cmd, pastcmd);
            free(input);
            free(cmd);

        }

    }
}


void commandExe(char* input, char* cmd, char* pastcmd){

    if(strcmp(cmd, "exit") == 0){
        my_exit(input);
    }
    else if(strcmp(cmd, "echo") == 0){
        echo(input);
        strcpy(pastcmd, input);
    }
    else if(strcmp(cmd, "!!") == 0){
        twoBangs(pastcmd);
        strcpy(pastcmd, input);
    }
    else{
        createForegroundProcess(cmd, input);
        strcpy(pastcmd, input);
    }
}


//MileStone 3

//retoknize the input
void createForegroundProcess(char* cmd, char* input){
    int status; 
    int pid;

    if((pid = fork()) < 0){
        perror("Fork failed");
        exit(errno);
    }

    if(!pid){

        execvp(cmd, &input);
        exit(1);
    }

    if(pid){
        waitpid(pid, &status, 0);
    }
}
