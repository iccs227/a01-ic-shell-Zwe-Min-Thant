#ifndef COMMANDEXE_H
#define COMMANDEXE_H

void commandExe(char* input, char* cmd, char* pastcmd, int last_status);
void IOcheckandreturnString(char* input, int* inflag, int* outflag, char* inFile, char* outFile);

#endif