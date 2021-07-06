#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <math.h>

#define n 10

pthread_t thread_id[n];

//Global variable
int g=0;

void * incr(void * arr)
{

    //static integer
    static int s=0; 
    
    //increment both integers
    s++;
    g++;
    
    //return the static variable after typecasting
    return (void *)s;
}

int main(int argc, char * argv[])
{
    printf("Global var is %d.\nStatic variable is initially 0.\n------------------\n",g);
    void *ret;
    int *s;
    for(int i=0;i<n;i++)
    {
	    pthread_create(&thread_id[i], NULL, incr, NULL);
	    pthread_join(thread_id[i],&ret);   // receive return value ((void)static int) in ret variable
	    s=(int *)ret;                      // get integer
    }
    printf("Global variable is now %d.\nStatic Variable is now %d\n",g,s);  // print final value of global and static variable
    pthread_exit(NULL);
}

