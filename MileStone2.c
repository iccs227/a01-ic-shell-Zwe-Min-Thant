#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./MileStone2.h"
#include "./MileStone1.h"
#include "./Toknizer.h"

extern int loop;
extern int exit_code;

void fileExe(FILE* fp, char* pastcmd, char* input) {
    while(fgets(input, 225, fp) != NULL){
        input[strcspn(input, "\n")] = 0;
        char* cmd = commandChecker(input);
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
            printf("Please type a valid command\n");
        }
        free(cmd);
    }
}