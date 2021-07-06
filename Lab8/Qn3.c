#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <pthread.h> 

#define left pos%5
#define right (pos+1)%5



pthread_t pthread_id[5];
pthread_mutex_t Mutex1;
pthread_mutex_t Mutex2;

#define n 5

int AllocM[5][5];
int ReqM[5][5];
int curr=0; 
int spoons[5];	
int Phil_Id[5]={0,1,2,3,4}; 


int getRandomPhilosopher()
{
    int phil=rand()%5;
    return phil;
}

void printInfo()
{
	pthread_mutex_lock(&Mutex2);
	
	printf("Allocation Matrix : \n");
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
				printf("%d ",AllocM[i][j]);
		}
		printf("\n");
	}	
		
	printf("Request Matrix : \n");
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
				printf("%d ",ReqM[i][j]);
		}
		printf("\n");
	}
	
	pthread_mutex_unlock(&Mutex2);
	return ;
}

void fn(int pos,int p)
{
    spoons[p]=0;	
	ReqM[pos][p]=0;	
	AllocM[pos][p]=1;	
}

int fn1(int pos,int p)
{
	return p==right && AllocM[pos][left]==0;
}

void pick(int pos,int p)
{
	if(p==right && AllocM[pos][left]==0 )	return;

	while(!spoons[p])
	{
		if(fn1(pos,p))
		{
			ReqM[pos][p] = 0;
			return;
		}
	}
	
	
	pthread_mutex_lock(&Mutex1);
	fn(pos,p);
	pthread_mutex_unlock(&Mutex1);
	return;
}

void pre_empt(int pos,int side)
{
	AllocM[pos][side]=0;	
	spoons[side]=1;
	return;
}

void check_deadlock()
{
    // If someone is eating , no deadlock exists
	if(curr>0) return;	

	// if some spoon is free, no deadlock
	for(int i=0;i<5;i++) if(spoons[i]) return ;
	
	
	sleep(1);
	if(curr > 0) return;

	printf("Deadlock detected\n");
	
	int x=getRandomPhilosopher();
	pre_empt(x,x);
	printf("Philosopher %d has been pre-empted\n", x);
	printInfo();
	return;
}

int notEating(int pos)
{
    return AllocM[pos][left]==0 && AllocM[pos][right]==0;
}


// Main function to be executed by thread
void *dinner(void* p)
{
	int pos=*((int*)p);
	while(1)
	{
	   // start thinking by freeing up left and right spoon
	   printf("Philosopher %d thinking\n",pos);
	   ReqM[pos][left]=0;
	   ReqM[pos][right]=0;
	   sleep(1);
	   
	   // Becomes hungry after thinking
	   // Try to take left fork
	   printf("Philosopher %d takes his left spoon %d\n",pos,left);
	   ReqM[pos][left]=1;
	   pick(pos,left);
	   
	   
	   // Try to pick right fork now
	   ReqM[pos][right]=1;
	   sleep(1);
	   pick(pos,right);
	   
	   // If left and right were not allocated to him, he can't eat
	   
	   if(notEating(pos)) continue;
	   
	   // He can  now take right spoon and start eating
	   
	   printf("Philosopher %d has taken right spoon %d and has started eating\n",pos,right);
	   
	   
	   // Number of philosopher eating has just increased by 1
	   curr++;
	   
	   // Eat for 2 second
	   sleep(2);
	   
	   // End eating and keep left and right spoon
	   
	   pre_empt(pos,left);
	   pre_empt(pos,right);
	   
	   
	   // Number of philosopher eating has reduced by 1
	   curr--;

	}
	pthread_exit(0);
}


// Initialise the matrices
void initialise()
{
  for(int i=0;i<5;i++)
  {
     for(int j=0;j<5;j++)
     {
     		AllocM[i][j]=0;
     		ReqM[i][j]=0;
     }
  }
  
  for(int i=0;i<5;i++) spoons[i]=1;
  return ;
}

int main()
{

	srand(0);
	
	if(pthread_mutex_init(&Mutex1,NULL))  printf("Failed");
	if(pthread_mutex_init(&Mutex2,NULL))  printf("Failed");

	for(int i=0;i<5;i++)  if(pthread_create(&pthread_id[i],NULL,dinner,&Phil_Id[i]))   printf("Failed");
	initialise();
	//Checks for deadlock
	while(1)  check_deadlock();

	for(int i = 0; i < 5; i++)   pthread_join(pthread_id[i],NULL);

	pthread_mutex_destroy(&Mutex1);
	pthread_mutex_destroy(&Mutex2);

	return 0;
}
