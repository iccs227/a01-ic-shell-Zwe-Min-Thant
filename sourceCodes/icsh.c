/* ICCS227: Project 1: icsh
 * Name: Zwe Min Thant
 * StudentID: 6581183
 */

#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "./headers/Toknizer.h"
#include "./headers/MileStone1.h"
#include "./headers/icsh.h"
#include "./headers/MileStone2.h"


int loop; 
int exit_code;

int main(int argc, char* argv[]) {
    char* input; 
    char* cmd;
    loop = 1; 
    char* pastcmd = malloc(225 * sizeof(char));

    if(argc > 1){
        FILE* fp = fopen(argv[1], "r");
        if(fp == NULL){
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
        else{
            input = malloc(225 * sizeof(char));
            fileExe(fp, pastcmd, input);
            fclose(fp);
            free(input);
            free(pastcmd);
            return 0;
        }
    }

    else{
        while(loop != 0){
            input = toknizer();
            cmd = commandChecker(input); 

            if(strcmp(cmd, "exit") == 0){
                my_exit(input);
            }
            else if(strcmp(cmd, "echo") == 0){
                echo(input);
                strcpy(pastcmd, input);
                free(input);
            }
            else if(strcmp(cmd, "!!") == 0){
                twoBangs(pastcmd);
                strcpy(pastcmd, input);
                free(input);
            }
            else{
                printf("Please type a valid command\n");
                free(input);
            }
        }
    }
}

