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
	   sleep(5);
	   // Parent has completed execution and this child has became orphan process
	   printf("\nI am child (pid = %d) (parent pid = %d)\n",getpid(),getppid());
	}
	else 
	{
		printf("\nI am parent (pid = %d) (child pid = %d)\n",getpid(),PID);
	}
	return 0;
}
