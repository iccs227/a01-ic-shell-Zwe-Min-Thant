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
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "../headers/Toknizer.h"
#include "../headers/icsh.h"
#include "../headers/commandExe.h"




int loop; 
int exit_code;
int background = 0;
int fg_pid = -1;
int last_status;
int IOredirectFlags = 0;
process jobs[16];



int main(int argc, char* argv[]) {

    struct sigaction sa;
    struct sigaction sa2;
    struct sigaction sa3;

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

    sa3.sa_handler = ChildHandler; 
    sigemptyset(&sa3.sa_mask);
    sa3.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa3, NULL);


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
            strcpy(pastcmd, input); 
            char* cmd = commandChecker(input);
            commandExe(input, cmd, pastcmd, last_status);
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
            commandExe(input, cmd, pastcmd, last_status);
            strcpy(pastcmd, input); 
            free(input);
            free(cmd);
        }
    }
}





//MileStone 3

//retoknize the input
void createForegroundProcess(char* cmd, char* input, int background){

    int status;
    int pid;
    int i = 0;
    int inflag = 0, outflag = 0;
    char* infile = malloc(100 * sizeof(char)); 
    char* outfile = malloc(100 * sizeof(char));
    char* inputcpy = malloc(225 * sizeof(char));
    char *argv[100];    
    IOcheckandreturnString(input, &inflag, &outflag, infile, outfile);



    strcpy(inputcpy, input);
    char *token = strtok(inputcpy, " \t\n");
    while(token != NULL && i < 100){
        if(strcmp(token, "<") == 0 || strcmp(token, ">") == 0){
            break; 
        }
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    argv[i] = NULL;

    pid = fork();


    if(pid < 0){
        perror("Fork failed");
        free(infile);
        free(outfile);
        free(inputcpy);
        exit(errno);
    }

    if(pid == 0){
        setpgid(0, 0);
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        if(inflag){
            
            int in_fd = open(infile, O_RDONLY);
            if(in_fd < 0){
                perror("Error opening input file");
                free(infile);
                free(outfile);
                free(inputcpy);
                exit(errno);
            }
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        
        if(outflag){
            int out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(out_fd < 0){
                perror("Error opening output file");
                free(infile);
                free(outfile);
                free(inputcpy);
                exit(errno);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }


        execvp(cmd, argv);
        perror("Execvp failed");
        free(infile);
        free(outfile);
        free(inputcpy);
        exit(errno);
    }


    if (pid > 0){

        setpgid(pid, pid);

        if(!background){
            fg_pid = pid;
            tcsetpgrp(STDIN_FILENO, pid);
            waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpid());
            if(WIFEXITED(status)){
                last_status = WEXITSTATUS(status);
            }   
            else if(WIFSIGNALED(status)){
                last_status = 128 + WTERMSIG(status);
            }
            else if(WIFSTOPPED(status)){
                last_status = 128 + WSTOPSIG(status);
                addjob(pid, input, "STOPPED");
                int jid = getjidbypid(pid);
                printf("[%d] %s \t \t \t %s", jid, jobs[jid-1].status, jobs[jid-1].cmd);

            }
            else{
                last_status = -1;
            }

            fg_pid = -1;
        }
        else{
            addjob(pid, input,"RUNNING");
            int jid = getjidbypid(pid);;
            printf("[%d] %d\n", jid, pid);
            fg_pid = -1;
        } 
    }
    free(infile);
    free(outfile);
    free(inputcpy);
}

//MileStone 4
void sigtstp(int sig){
    if(fg_pid > 0){
        kill(fg_pid, SIGTSTP);
        jobs[getjidbypid(fg_pid) - 1].status = "STOPPED";
    }
}

void sigint(int sig){
    if(fg_pid > 0){
        kill(-fg_pid, SIGINT);
    }
}

void addjob(int pid, char* input, char* status){
    for(int i = 0; i < 16; i++){
        if(jobs[i].pid == 0){
            jobs[i].pid = pid; 
            strcpy(jobs[i].cmd, input);
            jobs[i].cmd[255] = '\0'; 
            jobs[i].status = status;
            return;
        }
    }
}

void commandForeGround(int jid){

    int pid = getpidbyjid(jid);
    if(pid == -1){
        printf("Job do not exits\n");
        return;
    }
    int status;
    fg_pid = pid; 
    tcsetpgrp(STDIN_FILENO, pid);

    if(strcmp(jobs[jid - 1].status, "STOPPED") == 0){
        kill(pid, SIGCONT);
        jobs[jid - 1].status = "RUNNING";
        printf("Job [%d] %d resumed\n", jid, pid);
    }

    waitpid(-fg_pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpid());

    if(WIFEXITED(status)){
        last_status = WEXITSTATUS(status);
        printf("[%d] DONE \t\t\t %s \n", jid, jobs[jid - 1].cmd);
        jobs[jid - 1].pid = 0;
        strcpy(jobs[jid - 1].status, "DONE");
        jobs[jid - 1].cmd[0] = '\0';
    }   
    else if(WIFSIGNALED(status)){
        last_status = 128 + WTERMSIG(status);
        printf("[%d] been signaled \t\t\t %s \n", jid, jobs[jid - 1].cmd);
        jobs[jid - 1].pid = 0;
        strcpy(jobs[jid - 1].status, "DONE");
        jobs[jid - 1].cmd[0] = '\0';
    }
    fg_pid = -1;
}


int getpidbyjid(int jid){
    if(jobs[jid -1].pid != 0){
        return jobs[jid - 1].pid; 
    }
    else return -1; 
}

void commandBackGround(int jid){

    int pid = getpidbyjid(jid);

    if(pid == -1){
        printf("Job do not exits\n");
        return; 
    }

    if(strcmp(jobs[jid - 1].status, "STOPPED") == 0){
        kill(pid, SIGCONT);
        jobs[jid - 1].status = "RUNNING";
        printf("[%d] %s", jid, jobs[jid - 1].cmd);
    }

    else{
        printf("Job [%d] is not stopped\n", jid);
    }    
}

void ChildHandler(int sig){
    int status; 
    int pid; 

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        
        int jid = getpidbyjid(pid);
        if(WIFEXITED(status) || WIFSIGNALED(status)){
            printf("[%d] DONE \t\t\t %s \n", jid, jobs[jid - 1].cmd);
            jobs[jid - 1].pid = 0;
            jobs[jid - 1].status = "DONE";
            jobs[jid - 1].cmd[0] = '\0';
        }
    }
}


void printJobs(){
    for(int i = 0; i < 16; i++){
        if(jobs[i].pid != 0){
            printf("[%d] %s \t \t \t %s \n", i + 1, jobs[i].status, jobs[i].cmd);
        }
        else{
            return;
        }
    }
}

int getjidbypid(int pid) {
    for (int i = 0; i < 16; i++) {
        if (jobs[i].pid == pid)
            return i + 1; 
    }
    return -1;
}