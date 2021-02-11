#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	printf("argc = %d\n", argc);

	for (int i = 0; i < argc; i++) {
		
		printf("argv[%d] = ", i);
		puts(argv[i]);
		printf("\n");
	}
	printf("\n");

	int i = 0;
        while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
    	printf("\n");
}
