#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long int
#define ll signed long long int
#define pb push_back
#define mpp make_pair
#define mod 1000000007
#define pi 3.1415926536
#define N 100005
#define pp pair<int, int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vll vector<vector<ll>>
#define ms(a, v) memset(a, v, sizeof(a))
#define sortv(a) sort(a.begin(), a.end())
#define range(i, a, b, c) for (int i = a; i < b; i += c)
#define inf 10000000000000000


int _maxM[100][100];
int maxM[100][100];
int _alloc[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int finish[100];


int n,r;
int i,j;

int flag=0;


// User input from file
void all_input()
{
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif
}


/*

3 2
2 4 5
3 4 5
4 3 4
5 6 2
2 2

*/

void solve(){
  while(1){
  //printf("While loop\n");
    for(flag=0,i=0;i<n;i++){
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
  printf("Enter number of processes, resources : ");
  scanf("%d%d",&n,&r);
  printf("\nEnter allocation matrix : \n");
  for(j=0;j<r;j++)
  {
    for(i=0;i<n;i++)
    {
      scanf("%d",&_alloc[i][j]);
    }
  }
  printf("Enter max matrix\n");

  for(j=0;j<r;j++)
  {
    for(i=0;i<n;i++)
    {
      scanf("%d",&_maxM[i][j]);
    }
  }

  printf("Enter available matrix\n");

  for(i=0;i<r;i++)
    scanf("%d",&avail[i]);

 for(int i=0;i<n;i++)
 {
    for(int j=0;j<r;j++)
    {
    	maxM[i][j]=_maxM[j][i];
    }
 }

  for(int i=0;i<n;i++)
  {
    for(int j=0;j<r;j++)
    {
    alloc[i][j]=_alloc[j][i];
    }
  }



  for(i=0;i<n;i++)
  {
    for(j=0;j<r;j++)
    {
      need[i][j]=maxM[i][j]-alloc[i][j];
    }

  solve();

  int pro;
  for(pro = 0; pro<n; pro++){
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
}
