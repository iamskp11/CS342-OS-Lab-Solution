/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define h printf("Hello\n");
#define e exit(0);

int main(int argc,char *argv[])
{
    pid_t PID1,PID2;
    PID1=fork();
    if(PID1==0)
    {
       PID2=fork();
	       if(PID2==0)
		{       
			fork();
			h
			e
		}
		else 
		{
			h
			e
		}
    }
    else 
    {
    	fork();
    	h
    	e
    }
    e
}

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


// Function to print Hello
void h()
{
 	printf("Hello ");
}


// Function to terminate process
void e()
{
	exit(0);
}





int main(int argc, char *argv[])
{
	pid_t PID1,PID2;   // variables of datatype pid_t to store the return types of fork() and wait()
	PID1=vfork();      // create a child process


	if(PID1==0)
	{
		PID2=vfork();   // create a child process
			if(PID2==0)
			{
				vfork();
				//Print hello and exit
				h();
				e();
			}
			else
			{
				//Print hello and exit
				h();
				e();
			}

	}
	else
	{
		PID1=vfork();  // create a child process
		if(PID1)
		goto c;   // go and print Hello
		else h();
		//hello;
		e();   // exit

	}
	
	//create a label to print Hello
	c:
	printf("Hello\n");
	
	
}
