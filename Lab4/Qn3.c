#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>


bool prime(int a)
{
   if(a<=1) return false;
   for(int i=2;i*i<=a;i++)
   {
   	if(a%i==0) 
   	{
   		return false;
   	}
   }
   return true;
}

int main()
{
 
  
  int fd[2],fd1[2];
  	if(pipe(fd)==-1)
	{
		printf("Can't send infos\n");
	}
	if(pipe(fd1)==-1)
	{
		printf("Can't send infos\n");
	}
	 pid_t PID=fork();
  if(PID==0)
  {
  	printf("Enter n (length of Fibonacci array) : ");
  	int n;
  	scanf("%d",&n);
  	int fib[n+1];
  	fib[0]=0;
  	fib[1]=1;
  	for(int i=2;i<=n;i++) fib[i]=fib[i-1]+fib[i-2];
  	
  	//send the n to parent process
  	
	close(fd1[0]);
	write(fd1[1],&n,sizeof(n));
	close(fd1[1]);
	
  	//send the fib array to parent process
	close(fd[0]);
	write(fd[1],&fib,sizeof(fib));
	close(fd[1]);
  }
  else 
  {
  	wait(NULL);
  	//receive n from child
  	int n;
        close(fd1[1]);
        read(fd1[0],&n,sizeof(n));
        close(fd1[0]);
    
        //receive fib array from child
  	int fib[n+1];
        close(fd[1]);
        read(fd[0],&fib,sizeof(fib));
        close(fd[0]);
        
        printf("The Fibonacci series upto n=%d is\n",n);
        for(int i=0;i<=n;i++) printf("%d ",fib[i]);
        printf("\nThe prime numbers in this series are\n");
        for(int i=0;i<=n;i++)
        {
        	if(prime(fib[i])==false) continue;
        	printf("idx = %d, num= %d\n",i,fib[i]); 
        }
  }
 return 0;
}
