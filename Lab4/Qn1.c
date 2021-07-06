#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

int main()
{

	pid_t PID;
	PID=fork();

	if(PID==0)
	{
	   printf("I am child (pid = %d) (parent pid = %d)\n",getpid(),getppid());
	}
	else 
	{
		sleep(5);
		//The child process has now became zombie process
		printf("I am parent (pid = %d) (child pid = %d)\n",getpid(),PID);
	}
	return 0;
}
