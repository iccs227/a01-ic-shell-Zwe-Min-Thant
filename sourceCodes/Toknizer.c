#include <stdio.h>
#include <stdlib.h>
#include "./headers/Toknizer.h"


#define buffsize 255


int main(void){

	char* input = toknieze();
	char* cmd = commandChecker;

	printf("%s\n", input);
	printf("%s\n", cmd);

	return 0; 
	
}


char* toknizer(void){
	
	int buffersize = buffsize;
	int pos = 0; 
	char *buffer = malloc(sizeof(char) * buffersize); 
	int c; 

	while(1){
		printf("icsh $ ");
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
			buffersize += buffersize;
			buffer = realloc(buffer, buffersize);
		}
	}
}

char* commandChecker(char* input){

	char* cmd = strtok(input, " ");
	return cmd;

}
