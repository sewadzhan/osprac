#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pipe_par[2], pipe_ch[2];
    int result;
    size_t size;
    char resstring[14];

    if (pipe(pipe_par) < 0) {
        printf("Can not create parent pipe\n");
        exit(-1);
    }

    if (pipe(pipe_ch) < 0) {
        printf("Can not create child pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can not fork\n");
        exit(-1);
    } else if (result > 0) {
        close(pipe_par[0]);
        close(pipe_ch[1]);
        size = write(pipe_par[1], "Hello, world!", 14);

        if (size != 14) {
            printf("Can not write\n");
            exit(-1);
        }

        close(pipe_par[1]);

        size = read(pipe_ch[0], resstring, 14);

        if (size != 14) {
            printf("Can not read from child\n");
            exit(-1);
        }

        printf("Parent got result from child: %s\n", resstring);
        printf("Parent exit\n");
    } else {
        close(pipe_par[1]);
        close(pipe_ch[0]);
        size = read(pipe_par[0], resstring, 14);

        if (size < 0) {
            printf("Can not get from parent\n");
            exit(-1);
        }

        printf("Result from parent: %s\n", resstring);
        
        for (int i = 0; i < 13; i++) {
            char t = resstring[i];
	    if (t == 'o') {
            	resstring[i] = '@';
	    }
	    if (t == '!') {
            	resstring[i] = '?';
	    }
    	}

        size = write(pipe_ch[1], resstring, 14);
        close(pipe_par[0]);
        printf("Exit child\n");
    }
    return 0;
}
