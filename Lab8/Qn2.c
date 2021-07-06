#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 4     // Given number of questions

pthread_t thread_id[MAX_THREADS];    
int primes[10001];
int totsum;

int lock=0;
void sieve()
{
	for(int i=2;i<=10000;i++) primes[i]=1;
    primes[0]=0;
    primes[1]=0;
    for(int i=2;i<=100;i++) 
    {
       for(int j=i*i;j<=10000;j+=i)  primes[j]=0;
    }
}

// function for thread 
void * fn(void * arg)
{
	if(lock==1) 
	{  
	   while(lock==1) ;
	}
	lock=1;
    int st=(int *) arg;
    int en=(st+1);
    for(int i=st*2500;i<en*2500;i++)
    {
       if(primes[i]) 
       {
       //printf("%d is prime\n",i);
       totsum+=i;
       }
    }
    lock=0;
    pthread_exit(NULL);
}

int main()
{
	sieve();

    for(int i=0;i<4;i++)
    {
        pthread_create(&thread_id[i], NULL, fn, (void *)i);
    }
    sleep(3);
    printf("Sum is %d\n",totsum);
    pthread_exit(NULL);
  
}


