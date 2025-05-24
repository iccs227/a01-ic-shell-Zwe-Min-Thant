#include <stdio.h>
#include "./headers/MileStone1.h"
#include "./headers/icsh.h"

int main(void){
	return 0;
} 


void echo(char* String){
	char* str = strok(String, " ");
	str = strtok(NULL, " ");

	while(str != NULL){
		printf("%s", str); 
		str = strtok(NULL, " ");
	}

	printf("%s", String);
}

void twoBangs(char* String){
	printf("%s", String);
	echo(String);
}

void my_exit(char *String){
	exit_code = strtol(String, NULL, 10);
	if(exit_code < 0 || exit_code > 225){ 
		exit_code = exit_code & 0xFF;
	}
	loop = 0; 
}

