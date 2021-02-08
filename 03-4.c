#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid = fork();

	if (pid == -1) {
	    	printf("Error!\n");
	  	exit(-1);
	} else if (pid == 0) {
	   	printf("This is child process.\n");
		printf("This program launchs 03-3.c from child process");
		execl("03-3.c", "Hello", "parent");
	} else {
	    	printf("This is parent process.\n");
	}
}
