#ifndef ICSH_H
#define ICSH_H

void commandExe(char* cmd, char* input, char* pastcmd);
void createForegroundProcess(char* cmd, char* input, int background);
void sigtstp(int sig);
void sigint(int sig);

#endif