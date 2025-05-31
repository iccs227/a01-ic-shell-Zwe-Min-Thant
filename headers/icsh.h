#ifndef ICSH_H
#define ICSH_H

void createForegroundProcess(char* cmd, char* input, int background);
void sigtstp(int sig);
void sigint(int sig);
void addjob(int pid, char* input, char* status);
int getpidbyjid(int jid);
void commandBackGround(int jid);
void commandForeGround(int jid);
void ChildHandler(int sig);
void printJobs();
int getjidbypid(int pid);

typedef struct{
    int pid; 
    char cmd[255];
    char* status;
} process;


#endif