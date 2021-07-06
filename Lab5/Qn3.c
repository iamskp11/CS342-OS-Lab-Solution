#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <math.h>

void * calc(void * arr)
{
    // create double array of size 1000
    double *ret = malloc(sizeof(double)*1000);
    for(int i=0;i<1000;i++) ret[i]=cbrt(i*1.0);
    
    return (void *)ret;
}

int main(int argc, char * argv[])
{
    pthread_t thread_id;
    void *ret;
    double *ans;
    pthread_create(&thread_id, NULL, calc, NULL);
    printf("Computation under process... Plz wait\n");
    pthread_join(thread_id,&ret);
    ans=(double *)ret;
 
    for(int i=0;i<1000;i++) printf("Cube root of %d ---> %lf\n",i,ans[i]);
    pthread_exit(NULL);
}


