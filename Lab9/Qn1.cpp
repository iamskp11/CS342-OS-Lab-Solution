#include <bits/stdc++.h>
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

int n, r;
int flag = 0;

void all_input()
{
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif
}

int i,j;
/*
3 2
2 4 5
3 4 5
4 3 4
5 6 2
2 2
*/
void solve(vector<int>& avail, vector<vector<int>>& need, vector<int>& finish, vector<vector<int>>& alloc)
{
/*
    while (1)
    {
    	printf("QHil loop\n");
        for (flag=0, i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < r; j++)
                {
                	if(need[i][j]<=avail[j]) continue;
                    if (need[i][j] > avail[j])
                    {
                        //poss = 0;
                        break;
                    }
                }
                if (j==r)
                {
                	printf("In for %d\n",i);
                    for (j = 0; j < r; j++)
                        avail[j] += alloc[i][j];
                    flag = 1;
                    finish[i] = 1;
                }
            }
        }
        if (!flag)
            break;
     }
     */
     while(1){
  printf("While loop\n");
    for(flag=0,i=0;i<n;i++){
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

void print(vector<vector<int> >& c,int n,int r)
{
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<r;j++) cout<<c[i][j]<<" ";
    	cout<<endl;
    }
}

int main()
{
    //all_input();
    printf("Simulation of Deadlock Prevention\n");
    printf("Enter total number of processes, resources : ");
    cin >> n >> r;

    vector<vector<int>> _alloc(r, vector<int>(n, 0));
    vector<vector<int>> alloc(n, vector<int>(r, 0));
    printf("Enter the allocation matrix : \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < n; j++)
            cin >> _alloc[i][j];
    }
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<r;j++) alloc[i][j]=_alloc[j][i];
	}
    vector<vector<int>> _maxM(r, vector<int>(n, 0));
    vector<vector<int>> maxM(n, vector<int>(r, 0));
    cout << "Enter the max matrix\n";
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> _maxM[i][j];
    }
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<r;j++) maxM[i][j]=_maxM[j][i];
	}

    vector<int> avail(r, 0);
    cout << "Enter available matrix : ";
    for (int i = 0; i < r; i++)
        cin >> avail[i];

    vector<vector<int>> need(n, vector<int>(r, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
            need[i][j] = maxM[i][j] - alloc[i][j];
    }

    vector<int> finish(n, 0);
    //print(avail,n,r);
    print(need,n,r);
    print(alloc,n,r);
    solve(avail, need, finish, alloc);
    
    for(int idx=0;idx<n;idx++)
    {
        if(flag ==0 and finish[idx]!=1)
        {
        cout<<"Failing Mutual Exclusion\n";

        for(j=0;j<r;j++)
        {
            if(avail[j]<need[idx][j]) avail[j]=need[idx][j];

        }

        solve(avail, need, finish, alloc);

        if(finish[idx]==1) 
        {
            cout<<"By allocating required resources to process "<<i<<" dead lock is prevented\n";
        }

        cout<<"Lack of preemption\n";

        for(j=0;j<r;j++)
        {
            if(avail[j]<need[idx][j]) avail[j]=need[idx][j];
            alloc[idx][j]=0;
        }

        solve(avail, need, finish, alloc);

        if(finish[idx]==1)
        {
            cout<<"Deadlock is prevented by allocating needed resources\n";
        }

        cout<<"Faling : Hold and Wait condition\n";
        for(j=0;j<r;j++)
        {
            if(avail[j]<need[idx][j]) avail[j]=need[idx][j];

        }
        solve(avail, need, finish, alloc);
        }
    }
    return 0;
}
