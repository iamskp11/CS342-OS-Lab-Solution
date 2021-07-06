#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int c1=-1,c2=-1;
int main(int argc,char* argv[])
{

int a=atoi(argv[1]);
int b=atoi(argv[2]);
//int c1=-1,c2=-1,par;

int fd[2];
			if(pipe(fd)==-1)
			{
				printf("Can't send infos\n");
			}
pid_t PID,PID1,PID2;   // variables of datatype pid_t to store the return types of fork() and wait()
PID=fork();

if(PID==0)
{
   
   c1=a*b;
   
   //send the data to parent process
    close(fd[0]);
    write(fd[1],&c1,sizeof(c1));
    close(fd[1]);
   
   printf("Sum by C1 ( pid= %d ):  %d\n",getpid(),a*b);
   //exit(0);
   
}
else 
{
   //receive data from c1 
   int rec1;
   close(fd[1]);
   read(fd[0],&rec1,sizeof(rec1));
   close(fd[0]);
   
   int fd1[2];
   if(pipe(fd1)==-1) printf("Can't send rec2\n");
   
   PID1=wait(NULL);   // wait for all child processes to terminate
   PID=fork();        // create child process
   if(PID==0)  
   {
   	c2=a+b;
   	//send data to parent
   	//int fd[2];
   	//if(pipe(fd)==-1) printf("Can't send rec2\n");
   	close(fd1[0]);
        write(fd1[1],&c2,sizeof(c2));
        close(fd1[1]);
        
        
   	printf("Multiply by C2 ( pid= %d ): %d\n",getpid(),a+b);
   	//exit(0);
   }
   else 
   {
   	

        PID2=wait(NULL);    // wait for all child processes to terminate
        //receive data from c2
	   int rec2;
	   close(fd1[1]);
	   read(fd1[0],&rec2,sizeof(rec2));
	   close(fd1[0]);
        
   	printf("Division by P  (pid= %d ) :  %d\n",getpid(),rec2/rec1);
   	exit(0);
   }
}
exit(0);
}
