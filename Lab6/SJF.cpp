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
  while(count<n)
  {
      //cout<<"curr is "<<curr<<endl;
       int which=-1,mini=INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(process[i].first<=curr and !finished[i])
            {
                if(process[i].second<mini) 
                {
                    which=i;
                    mini=process[i].second;
                }
            }
            else if(process[i].first>curr) break;
        }
        if(which==-1)
        {
            for(int i=0;i<n;i++)
            {
                int done=0;
                if(process[i].first>curr)
                {
                    curr=process[i].first;
                    for(int j=i;j<n;j++)
                    {
                        if(process[j].first==process[i].first and !finished[j])
                        {
                            if(process[j].second<mini) 
                                {
                                    which=j;
                                    mini=process[j].second;
                                }
                        }
                        else if(process[j].first>process[i].first) 
                        {
                            done=1;
                            break;
                        }
                    }
                    if(done) break;
                }
                
            }
        }
        //cout<<"curr has become "<<curr<<endl;
        //cout<<"selected "<<which<<" mini is "<<mini<<endl;
        int processnum=which;
        finished[processnum]=1;
        int req=process[which].second;
        curr=max(curr,process[which].first)+req;
        completed[which]=curr;
        count++;
        order.pb(which);
  }
  //for(int i=0;i<n;i++) cout<<completed[i]<<" ";
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
