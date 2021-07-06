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
#define ms(a, v) memset(a, v, sizeof(a))
#define sortv(a) sort(a.begin(), a.end())
#define F(i, a, b, c) for (int i = a; i < b; i += c)
#define RF(i, a, b, c) for (int i = a; i >= b; i += c)
#define inf 10000000000000000


float fn(int a,int b)
{
    return (a*1.0)/(b*1.0);
}

int main()
{
  
  
  int n;
  cin>>n;
  pair<int,int> process[n];
  int completed[n];
  for(int i=0;i<n;i++)
  {
        cin>>process[i].first>>process[i].second;
  }
  sort(process,process+n);
  vector<int> completion;
  int curr=0;
  for(int i=0;i<n;i++)
  {
        int arrived=process[i].first;
        int req=process[i].second;
        if(arrived<=curr)  
        {
            curr=curr+req;
        }
        else 
        {
            curr=arrived+req;
        }
        completed[i]=curr;
        completion.pb(i+1);
  }
  int tat=0,wt=0;
  for(int i=0;i<n;i++)
  {
      tat+=completed[i]-process[i].first;
      wt+=(completed[i]-process[i].first-process[i].second);
  }
  printf("%.2f %.2f\n",fn(wt,n),fn(tat,n));
  for(int x : completion)
  {
      cout<<"P"<<x<<" ";
  }
  printf("\n");
  return 0;
}
