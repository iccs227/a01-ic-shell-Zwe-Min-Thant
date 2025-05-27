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
#include <signal.h>
#include "../headers/Toknizer.h"
#include "../headers/MileStone1.h"
#include "../headers/icsh.h"



int loop; 
int exit_code;
int fg_pid = -1;
int stopped_pid;

int main(int argc, char* argv[]) {
    struct sigaction sa;
    struct sigaction sa2;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);


    sa.sa_handler = sigint;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sa2.sa_handler = sigtstp;
    sigfillset(&sa2.sa_mask);
    sa2.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa2, NULL);

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
        input = strtok(input, " ");
	    input = strtok(NULL, " ");
        exit_code = strtol(input, NULL, 10);
        if(exit_code < 0 || exit_code > 225){ 
		    exit_code = exit_code & 0xFF;
	    }
        printf("BYE\n");
        exit(exit_code);
        
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
    int i = 0;
    char *argv[100];
    char *token = strtok(input, " \t\n");
    while(token != NULL && i < 100){
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    pid = fork();
    if(pid < 0){
        perror("Fork failed");
        exit(errno);
    }

    if(pid == 0){
        setpgid(0, 0);
        tcsetpgrp(STDIN_FILENO, getpid());
        printf("Child process created with PID: %d\n", getpid());
        execvp(cmd, argv);
        perror("Execvp failed");
        exit(errno);
    }


    if (pid){
        fg_pid = pid;
        setpgid(pid, pid);
        tcsetpgrp(STDIN_FILENO, pid);
        waitpid(pid, &status, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpid());
        fg_pid = -1;
    }

}

//MileStone 4
void sigtstp(int sig){
    if(fg_pid > 0){
        kill(fg_pid, SIGTSTP);
        stopped_pid = fg_pid;
    }
    else{
        printf("\n");
        printf("icsh $");
        fflush(stdout);
    }
}

void sigint(int sig){
    if(fg_pid > 0){
        kill(fg_pid, SIGINT);
    }
    else{
        printf("\n");
        printf("icsh $");
        fflush(stdout);
    }
}


void sendProcesstoFG() {

    if (stopped_pid == -1) {
        printf("No job to bring to foreground\n");
        return;
    }

    fg_pid = stopped_pid;
    tcsetpgrp(STDIN_FILENO, fg_pid);
    kill

}

