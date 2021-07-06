#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_THREADS 50      // Given number of questions

pthread_t thread_id[MAX_THREADS];    

// function for thread 
void * fn(void * arg)
{
    printf("Hello from groot %u - I was created in iteration %d !\n", (int)pthread_self(), (int)arg);
    pthread_exit(NULL);
}

int main(int argc, char * argv[])
{

    if(argc != 2) 
    {
        printf("Please give number of threads to be created (only)\n");
        exit(1); 
    }
    int n = atoi(argv[1]);
    if(n > MAX_THREADS || n<=0) n = MAX_THREADS;   // if n is negative of greater than 50, then keep n = 50

    for(int i=0;i<n;i++)
    {
        pthread_create(&thread_id[i], NULL, fn, (void *)i);
        printf("\n I am groot %u. Created new thread (%u) in iteration %d ...\n", (int)pthread_self(), (int)thread_id[i], i);
        if(i % 5 == 4) sleep(1);    // (0,1,2,3,4) --> sleep (1) --> (5,6,7,8,9) -->sleep(1)
    }

    pthread_exit(NULL);
}


