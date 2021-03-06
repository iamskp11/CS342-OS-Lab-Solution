#include<stdio.h>
int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int i,j,p,r;
int finish[100]={0};
int flag=0;

void all_input()
{
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif
}

void solve(){
  while(1){
  printf("While loop\n");
    for(flag=0,i=0;i<p;i++){
      if(finish[i]==0) {
        for(j=0;j<r;j++) {
          if(need[i][j]<=avail[j])
            continue;
          else
            break;
        }
        if(j==r) {
        printf("i=%d\n",i);
          for(j=0;j<r;j++)
            avail[j]+=alloc[i][j];
            flag=1;
            finish[i]=1;
        }
      }
    }
    if(flag==0)
       break;
  }
}


int main()
{
  //all_input();
  printf("SIMULATION OF DEADLOCK PREVENTION\n");
  printf("Enter number of processes, resources\n");
  scanf("%d%d",&p,&r);
  printf("Enter allocation matrix\n");
  int _max[r][p];
  int _alloc[r][p];

  for(j=0;j<r;j++)
    for(i=0;i<p;i++)
      scanf("%d",&_alloc[i][j]);
  printf("Enter max matrix\n");

  for(j=0;j<r;j++)
    for(i=0;i<p;i++)
      scanf("%d",&_max[i][j]);

  printf("Enter available matrix\n");

  for(i=0;i<r;i++)
    scanf("%d",&avail[i]);

 for(int i=0;i<p;i++)
    for(int j=0;j<r;j++)
    max[i][j]=_max[j][i];

  for(int i=0;i<p;i++)
    for(int j=0;j<r;j++)
    alloc[i][j]=_alloc[j][i];



  for(i=0;i<p;i++)
    for(j=0;j<r;j++)
      need[i][j]=max[i][j]-alloc[i][j];

  solve();

  int pro;
  for(pro = 0; pro<p; pro++){
    if(flag==0) {
      if(finish[pro]!=1){
        // 1
        printf("\n Failing :Mutual exclusion");
        for(j=0;j<r;j++){ /*checking for mutual exclusion*/
          if(avail[j]<need[pro][j])
            avail[j]=need[pro][j];
        }

        solve();
        if(finish[pro] == 1)
          printf("\n By allocating required resources to process %d dead lock is prevented ",pro);
        // 2

        printf("\n lack of preemption");
        for(j=0;j<r;j++){
          if(avail[j]<need[pro][j])
            avail[j]=need[pro][j];
          alloc[pro][j]=0;
        }

        solve();
        if(finish[pro] == 1)
          printf("\n daed lock is prevented by allocating needed resources");
        // 3

        printf(" \n failing:Hold and Wait condition ");
        for(j=0;j<r;j++){ /*checking hold and wait condition*/
          if(avail[j]<need[pro][j])
            avail[j]=need[pro][j];
        }
        solve();
        // avoiding any condition out of 3 can prevent deadlock
      }
    }
  }
 printf("\n");
}
