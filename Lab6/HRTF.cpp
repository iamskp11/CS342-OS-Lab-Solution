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
string add(int a,int b)
{
    return to_string(a)+"!"+to_string(b);
}

int main()
{
  multimap<string,int> mp;
  vector<int> order;
   int n;
  cin>>n;
  vector<pair<int,int> > process(n,{0,0});
  int completed[n];
  for(int i=0;i<n;i++)
  {
        cin>>process[i].first>>process[i].second;
        mp.insert({add(process[i].first,process[i].second),i});
  }
  sort(process.begin(),process.end());
  int finished[n],count=0;
  int curr=process[0].first;
  fill(completed,completed+n,0);
  fill(finished,finished+n,0);
  vector<pair<int,int> > ready=process;
  for(int t=curr;1;t++)
  {
       if(count==n) break;
        int maxi=INT_MIN,which=-1;
        for(int i=0;i<n;i++)
        {
            if(ready[i].first>t) break;
            if(ready[i].second>maxi and !finished[i])
            {
                maxi=ready[i].second;
                which=i;
            }
        }
        if(which==-1) continue;
        ready[which].second--;
        if(ready[which].second==0) 
        {
            finished[which]=1;
            completed[which]=t+1;
            order.pb(which);
            count++;
        }
  }
 // for(int i=0;i<n;i++) cout<<completed[i]<<" ";
  int wt=0,tat=0;
  for(int i=0;i<n;i++)
  {
      tat+=(completed[i]-process[i].first);
      wt+=(completed[i]-process[i].first-process[i].second);
  }
  printf("%.2f %.2f\n",fn(wt,n),fn(tat,n));
  
  for(int p: order)
  {
      int st=process[p].first;
      int brst=process[p].second;
      int idx=(mp.lower_bound(add(st,brst)))->second;
      cout<<"P"<<idx+1<<" ";
      mp.erase(mp.lower_bound(add(st,brst)));
  }
  printf("\n");
  return 0;
}
