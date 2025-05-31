
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/commandExe.h"
#include "../headers/MileStone1.h"
#include "../headers/icsh.h"

extern int background;

void commandExe(char* input, char* cmd, char* pastcmd, int last_status) {

    if(strchr(input, '<') != NULL || strchr(input, '>') != NULL) {
        createForegroundProcess(cmd, input, background);
        strcpy(pastcmd, input);
        printf("\n");
        return; 
    }

    if(strcmp(cmd, "jobs") == 0){
        printJobs(); 
        return; 
    }

    if(input[strlen(input) - 1] == '&'){
        background = 1; 
        input[strlen(input) - 1] = '\0';
        createForegroundProcess(cmd, input, background);
        background = 0; 
        return;
    }
    if(strcmp(cmd, "fg") == 0){
        input = strtok(input, " ");
        input = strtok(NULL, " ");
        if(input == NULL){
            printf("fg: missing job id\n");
            return;
        }
        input++;
        printf("fg: %s\n", input);
        int jid = atoi(input);
        printf("%d\n", jid);
        commandForeGround(jid);
        return;
    }

    if(strcmp(cmd, "bg") == 0){
        input = strtok(input, " ");
        input = strtok(NULL, " ");
        if(input == NULL){
            printf("fg: missing job id\n");
            return;
        }
        input++; 
        int jid = atoi(input);
        commandBackGround(jid);
        return;
    }

    if(strcmp(cmd, "exit") == 0){
        input = strtok(input, " ");
	    input = strtok(NULL, " ");
        printf("BYE\n");
        my_exit(input);
        return;
    }

    else if (strcmp(input, "echo $?") == 0) {
        printf("%d", last_status);
        return;
    }

    if(strcmp(cmd, "echo") == 0){
        echo(input);
        return;
    }

    if(strcmp(cmd, "!!") == 0){
        twoBangs(pastcmd);
        return;
    }

    if (input[strlen(input) - 1] == '&') {
        background = 1;
        input[strlen(input)-1] = '\0';
        createForegroundProcess(cmd, input, background);
        printf("\n");
        return;
    }

    else{
        createForegroundProcess(cmd, input, background);
        printf("\n");
        return;
    }

}


void IOcheckandreturnString(char* input, int* inflag, int* outflag, char* inFile, char* outFile) {\

    char* infilecpy = malloc(100 * sizeof(char));
    char* outfilecpy = malloc(100 * sizeof(char));
    strcpy(infilecpy, input);
    strcpy(outfilecpy, input);

    char* inptr = strchr(infilecpy, '<');
    if (inptr != NULL) {
        *inflag = 1;
        inptr++;
        while(isspace(*inptr)){
            inptr++;
        }
        char* token = strpbrk(inptr, " \t\n");
        if(token){
            *token = '\0';
        }
        printf("Input file: %s\n", inptr);
        strcpy(inFile, inptr);
    }
    
    char* outptr = strchr(outfilecpy, '>');
    if (outptr != NULL) {
        *outflag = 1;
        outptr++; 
        while (isspace(*outptr)){
             outptr++;
            }
        char* token = strpbrk(outptr, " \t\n");
        if (token) *token = '\0';
        strcpy(outFile, outptr);
    }
}