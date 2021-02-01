#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  //This program creates 3 children from one parent process
  pid_t pid, ppid;
  int a = 0;
  
  while	(a < 3) {
	fork();
  	a = a+1;
  }	
  
  pid  = getpid();
  ppid = getppid();

  printf("This pid = %d, this ppid = %d\n", (int)pid, (int)ppid);

  return 0;
}
