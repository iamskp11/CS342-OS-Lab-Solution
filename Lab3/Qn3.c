#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char* argv[])
{
        pid_t PID;   // variables of datatype pid_t to store the return types of fork() and wait()
        PID=fork();  //create a child process
        if(PID==0)
        {
        
        	// It is a child process. So, run Task1 , Task1 is stored as Qn1.sh
		char *file="Qn1.sh";
		char *arguments[]={"sh",file,NULL};
		execv("/bin/bash",arguments);
		
		exit(0);
	}
	else 
	{
		PID=wait(NULL);
		// It is a parent process. So, run Task2 , Task2 is stored as Qn2.sh
		char *file="Qn2.sh";
		
		//Task2 needed a number N as argument, which is passed as a CLA, so take input from user
		int N;
		printf("Enter number for Task2 : ");
		scanf("%d",&N);
		
		// Store the integer into character array to pass it as execv argument
		char res[3];
		sprintf(res,"%d",N);
		
		
		char *arguments[]={"sh",file,res,NULL};
		execv("/bin/bash",arguments);
		exit(0);
	}
	exit(0);
	return 0;
}
