
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./headers/Toknizer.h"


#define buffsize 255

char* toknizer(void){
	
	int buffersize = buffsize;
	int pos = 0; 
	char *buffer = malloc(sizeof(char) * buffersize); 
	int c; 
	printf("icsh $ ");
	while(1){
		c = getchar(); 
		
		if(c == EOF || c == '\n'){ 
			buffer[pos] = '\0';
			return buffer;
		}
		else{
			buffer[pos] = c; 
		}
		pos++; 

		if(pos >= buffersize){
			buffer = realloc(buffer, buffersize);
		}
	}
}

//correct 
char* commandChecker(char* input){
	char* cmd = malloc(strlen(input) + 1);
	strcpy(cmd, input);
	cmd = strtok(cmd, " ");
	return cmd;
}
