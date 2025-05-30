#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/MileStone1.h"

#include <unistd.h>

extern int loop;
extern int exit_code;

void echo(char* String){
	char* str = malloc(strlen(String) + 1);
	strcpy(str, String);
	str = strtok(str, " ");
	str = strtok(NULL, " ");
	
	while(str != NULL){
		printf("%s\n", str); 
		str = strtok(NULL, " ");
	}
	free(str);
}

void twoBangs(char* String){
	printf("%s\n", String);
	echo(String);
}

void my_exit(char *String){
	exit_code = strtol(String, NULL, 10);
	if(exit_code < 0 || exit_code > 225){
		exit_code = exit_code & 0xFF;
	}
	loop = 0;
}