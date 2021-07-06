#include<stdio.h>


int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int i,j,n,r;
int finish[100]={0};
int done=0;

void all_input()
{
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif
}

int driver(){
  while(1){
  //printf("While loop\n");
    for(done=0,i=0;i<n;i++){
      if(finish[i]==0) {
        for(j=0;j<r;j++) {
          if(need[i][j]<=avail[j])
            continue;
          else
            break;
        }
        if(j==r) {
        //printf("i=%d\n",i);
          for(j=0;j<r;j++)
            avail[j]+=alloc[i][j];
            done=1;
            finish[i]=1;
        }
      }
    }
    if(done==0)
       break;
  }
}

/*
3 2
2 4 5
3 4 5
4 3 4
5 6 2
2 2
*/

int main()
{
  //all_input();
  printf("SIMULATION OF DEADLOCK PREVENTION\n");
  
  
  printf("Enter number of processes, resources : ");
  scanf("%d%d",&n,&r);
  
  
  printf("Enter allocation matrix\n");
  
  int _alloc[r][n];

  for(j=0;j<r;j++)
    for(i=0;i<n;i++)
      scanf("%d",&_alloc[i][j]);
      
   
  printf("Enter max matrix\n");
  
  int _max[r][n];
  for(j=0;j<r;j++)
    for(i=0;i<n;i++)
      scanf("%d",&_max[i][j]);

  
  printf("Enter available matrix\n");

  for(i=0;i<r;i++)
    scanf("%d",&avail[i]);

 for(int i=0;i<n;i++)
    for(int j=0;j<r;j++)
    max[i][j]=_max[j][i];

  for(int i=0;i<n;i++)
    for(int j=0;j<r;j++)
    alloc[i][j]=_alloc[j][i];



  for(i=0;i<n;i++)
    for(j=0;j<r;j++)
      need[i][j]=max[i][j]-alloc[i][j];



  // Run driver function to check for mutual exclusion
  driver();


  for(int idx = 0; idx<n; idx++){
    if(done==0) {
      if(finish[idx]!=1){
        printf("\n Failing :Mutual exclusion");
        for(j=0;j<r;j++){ 
          if(avail[j]<need[idx][j])
            avail[j]=need[idx][j];
        }

        driver();
        if(finish[idx] == 1)
          printf("By allocating required resources to process %d dead lock is prevented\n",idx);

        printf("Lack of preemption\n");
        for(j=0;j<r;j++){
          if(avail[j]<need[idx][j])
            avail[j]=need[idx][j];
          alloc[idx][j]=0;
        }

        driver();
        if(finish[idx] == 1)
          printf("Dead lock is prevented by allocating needed resources\n");

        printf("Failing :Hold and Wait condition\n");
        for(j=0;j<r;j++){ 
          if(avail[j]<need[idx][j])
            avail[j]=need[idx][j];
        }
      }
    }
  }
}
