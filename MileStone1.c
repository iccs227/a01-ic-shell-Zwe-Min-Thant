#include <stdio.h>
#include "MileStone1.h"

int main(void){
	return 0;
} 


int echo(char* String){
	char* str = strok(String, " ");
	str = strtok(NULL, " ");

	while(str != NULL){
		printf("%s", str); 
		str = strtok(NULL, " ");
	}

	printf("%s", String);
	return 1;
}

int twoBangs(char* String){
	printf("%s", String);
	echo(String);
}

