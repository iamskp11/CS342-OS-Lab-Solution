#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

int isPrime[1<<20];   // If isPrime(i) == 1, it is not prime , else it is prime
void sieve()
{
	isPrime[1]=1;
	for(int i=2;i<=999;i++)
	{
		for(int j=i*i;j<(1<<20);j+=i)
		{
			isPrime[j]=1;
		}
	}
}

double divide(int i)
{
   double den=i*1.0;
   return 1/den;
}

int main()
{
	// Initialise pipe to send and receive the numbers
	sieve();
	int fd1[2],fd2[2],fd3[2];
  	if(pipe(fd1)==-1)
	{
		printf("Can't send infos\n");
	}
	if(pipe(fd2)==-1)
	{
		printf("Can't send infos\n");
	}
	if(pipe(fd3)==-1)
	{
		printf("Can't send infos\n");
	}
	
	
	int n;
	printf("Enter n : ");
	scanf("%d",&n);
	// This above n will be available to all processes
	pid_t PID;
	PID=fork();

	if(PID==0)
	{
		// I am child C1 
		// I will compute sum of positive non-primes and send it to parent
		
		
		// I will also create a child 
		pid_t PID1;
		PID1=fork();
		if(PID1==0)
		{
			// I will compute sum of positive primes and send it to my parent
			double PosPrimes=0;
			for(int i=1;i<=n;i+=2)
			{
				if(isPrime[i]==0) 
				{
					PosPrimes+=divide(i);
				}
			}
			double arr[3]={0,0,0};
			arr[0]=PosPrimes;
			// send arr to parent 
			close(fd1[0]);
			write(fd1[1],&arr,sizeof(arr));
			close(fd1[1]);
			
			
		}
		else 
		{
			wait(NULL);
			double arr[3];
			// receive arr from parent
			close(fd1[1]);
		    read(fd1[0],&arr,sizeof(arr));
		    close(fd1[0]);
			// I will compute sum of all positive non-primes and send it to my parent
			double PosNonPrimes=0;
			for(int i=1;i<=n;i+=2)
			{
				if(isPrime[i]==1) PosNonPrimes+=divide(i);
			}
			
			arr[1]=PosNonPrimes;
			// send arr to parent 
			close(fd2[0]);
			write(fd2[1],&arr,sizeof(arr));
			close(fd2[1]);
			
		}
	}
	else 
	{
		wait(NULL);
		double arr[3];
		// receive arr from parent
		close(fd2[1]);
	    read(fd2[0],&arr,sizeof(arr));
	    close(fd2[0]);
	    //for(int i=0;i<3;i++) printf("%f ",arr[i]);
	 	pid_t PID2;
	 	PID2=fork();
	 	if(PID2==0)
	 	{	
	 		//I will compute sum of all negative numbers and send it to parent
	 		double negs=0;
	 		for(int i=2;i<=n;i+=2)
	 		{
	 			negs-=divide(i);
	 		}
	 		
	 		arr[2]=negs;
	 		//for(int i=0;i<3;i++) printf("%f ",arr[i]);
	 		// send arr to parent 
			close(fd3[0]);
			write(fd3[1],&arr,sizeof(arr));
			close(fd3[1]);
	 	}
	 	else 
	 	{
	 		wait(NULL);
	 		double arr[3];
	 		// receive arr from parent
			close(fd3[1]);
			read(fd3[0],&arr,sizeof(arr));
			close(fd3[0]);
			double ans=0;
	 		for(int i=0;i<3;i++) ans+=arr[i];
	 		printf("Desired Ans is %.10f\n",ans);
	 	}
	 	
	}
	return 0;
}
