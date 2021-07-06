#include <bits/stdc++.h>
using namespace std;
#define pb push_back

int main()
{
	int n;
	cout<<"Number of processes : ";
	cin>>n;
	pair<int,int> info[n];
	//multimap<string,int> mp;
	int priority[n];
	int burst[n];
	cout<<"Enter details of each process (Arrival Time, Priority, Burst Time) :"<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>info[i].first>>priority[i]>>info[i].second;
		//mp.insert({info[i].first+"!"+priority[i]+"!"+info[i].second,i});
		burst[i]=info[i].second;
	}
	priority_queue<pair<pair<int,int> ,pair<int,int> > > pq;
	// Process whose priority number is more, has higher priority
	for(int i=0;i<n;i++)
	{
		pq.push({{priority[i],info[i].first},{i,info[i].second}});
	}
	vector<int> order;
	int completion[n];
	fill(completion,completion+n,-1);
	for(int timer=0;1;timer++)
	{
		if(order.size()==n) break;
		int idx=-1,pr=-1;
		for(int i=0;i<n;i++)
		{
			if(info[i].first>timer or completion[i]!=-1) continue; 
			if(priority[i]>pr)
			{
				pr=priority[i];
				idx=i;
			}
		}
		if(idx==-1) continue;
		info[idx].second-=1;
		if(info[idx].second==0)
		{
			completion[idx]=timer+1;
			order.pb(idx+1);
		}
	}
	int wt=0,tat=0;
	for(int i=0;i<n;i++)
	{
		tat+=completion[i]-info[i].first;
		wt+=completion[i]-info[i].first-burst[i];
	}
	cout<<"Average TurnAround time is "<<(tat*1.0)/n<<endl;
	cout<<"Average Waiting time is "<<(wt*1.0)/n<<endl;
	for(int i=0;i<n;i++) cout<<"P"<<order[i]<<" ";
	cout<<endl;
	return 0;
}
