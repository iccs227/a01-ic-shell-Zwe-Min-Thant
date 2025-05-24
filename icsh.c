/* ICCS227: Project 1: icsh
 * Name: Zwe Min Thant
 * StudentID: 6581183
 */

#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "./Toknizer.h"
#include "./MileStone1.h"


int loop; 
int exit_code;

int main() {

    char* input; 
    char* cmd;
    loop = 1; 
    char* pastcmd = malloc(225 * sizeof(char));
    
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

