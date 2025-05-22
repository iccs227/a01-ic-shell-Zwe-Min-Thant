/* ICCS227: Project 1: icsh
 * Name: Zwe Min Thant
 * StudentID: 6581183
 */

#include "stdio.h"
#include "Toknizer.h"
#include "MileStone1.h"

int main() {
    char* input; 
    char* cmd; 
    while(1){
        input = toknizer();
        cmd = commandChecker(input); 

        if(strcmp(cmd, "exit") == 0){
            return 0;
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

