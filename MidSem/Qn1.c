#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

int main() {
    pid_t PIDZombie;
    // Creating Zombie Child
    PIDZombie=fork();
    if(PIDZombie==0)
    {
        printf("Child1 : PID = %d Parent Id = %d\n",getpid(),getppid());
    }
    else
    {
      sleep(5);
      // Creating Orphan Child
      
      pid_t PIDOrphan=fork();
      
      if(PIDOrphan==0)
      {
      	 sleep(5);
         printf("Child2 : PID = %d Parent Id = %d\n",getpid(),getppid());
      }
      else
      {
      	 printf("Parent : PID = %d Child1 : %d Child2 : %d\n",getpid(),PIDZombie,PIDOrphan);
      }
        
    }
       
}
