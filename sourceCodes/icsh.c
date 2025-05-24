/* ICCS227: Project 1: icsh
 * Name: Zwe Min Thant
 * StudentID: 6581183
 */

#include "stdio.h"
#include "./headers/Toknizer.h"
#include "./headers/MileStone1.h"

    int loop;
    int exit_code;

int main() {

    char* input; 
    char* cmd; 

    while(loop != 0){
        input = toknizer();
        cmd = commandChecker(input); 

        if(strcmp(cmd, "exit") == 0){
            my_exit(input);
        }
        else if(strcmp(cmd, "echo") == 0){
            echo(input);
            input = toknizer(); 
            cmd = commandChecker(input);
        }
        else if(strcmp(cmd, "!!") == 0){
            twoBangs(input);
            input = toknizer();
            cmd = commandChecker(input);
        }
        else{
            printf("Please type a valid command\n");
            input = toknizer(); 
            cmd = commandChecker(input);
        }
    }
    
}

