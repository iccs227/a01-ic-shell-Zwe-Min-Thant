#include <stdio.h>
#include <string.h>



char toknizer(char* string); 

int main(){
	
	char string = "echo COMMANDS1 COMMANDS2 COMMANDS3";
	char arr[] = toknizer(string);
	for(int i = 0; i < sizeof(arr); i++){
		printf("%s\n", arr[i]);
	}
	return 0;
}

char toknizer(char* string){
	
	char arr[] = malloc(sizeof(char)*strlen(string));

	char* token = strtok(string, " ");
	
	int i = 0; 

	while(token != NULL){
		arr[i] = token;
		i++;
	}

	return arr;
	
}
