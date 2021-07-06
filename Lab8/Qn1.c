#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 2    // Given number of questions

pthread_t pthread1,pthread2;    

int lock=0;


// function for thread 
void * f(void * arg)
{
	if(lock) 
	{  
	   int curr=3-lock;
	   printf("thread%d can't access f() since thread%d is using it\n",curr,lock);
	   while(lock) 
	   {
	   
	   }
	}
	lock=(int) arg;
	printf("Lock acquired by %d\n",lock);
    // Critical Section
    printf("thread%d is using f()\n",lock);
    //
    sleep(2);
    printf("Lock released by %d\n",lock);
    lock=0;
    pthread_exit(NULL);
}

int main()
{
    pthread_create(&pthread1, NULL, f, (void *)1);
    pthread_create(&pthread2, NULL, f, (void *)2);
    sleep(3);
    pthread_exit(NULL);
  
}


