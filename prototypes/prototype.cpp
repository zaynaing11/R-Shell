#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

void parsecmd(char *cmd, char **argv){
	while(*cmd != '\0'){
		while(*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
			*cmd++ = '\0';
		*argv++ = cmd;
		while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t' && *cmd != '\n')
			cmd++;
	}
	*argv = '\0';
}

void runcmd(char **argv){

	pid_t pid;
	int status;

	if((pid = fork()) < 0){
		printf("Error: Fork Failed\n");
		exit(1);
	}
	else if(pid > 0){
		waitpid(pid, &status, 0);
	}
	else if(pid == 0){
		if(execvp(*argv, argv) < 0){
			printf("Error: Execution Failed\n");
			exit(1);
		}
	}
	else{
		while(wait(&status) != pid)
			;
	}
}
int main(){
	char line[1024];
	char *argv[64];

	while(1){
		printf("Shell -> ");
		fgets(line, 10, stdin);
		printf("\n");
		parsecmd(line, argv);
		if(strcmp(argv[0], "exit") == 0)
			exit(0);
		runcmd(argv);
	}
}



