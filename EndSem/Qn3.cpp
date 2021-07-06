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
#define vvi vector<vector<int> >
#define vl vector<ll>
#define vll vector<vector<ll> >
#define ms(a, v) memset(a, v, sizeof(a))
#define sortv(a) sort(a.begin(), a.end())
#define range(i, a, b, c) for (int i = a; i < b; i += c)
#define inf 10000000000000000

void fast()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

// Define structure of the process
struct processes
{
	char id;
	int arr_time;
	int burst_time;
};

// Variable to store number of processes, both time quantum and time instant
int n, d1,d2, inst;

int main()
{
    fast();
    // Take user input
    cin >> d1>>d2 >> n;

    // Check for invalid time quantum
    if(d1 < 0 or d2 < 0)
    {
    	cout<<"[-]Please enter valid time quantum\n";
    	return 0;
    }

    // Check for invalid number of processes
    if(n<0)
    {
    	cout<<"[-]Can't have negative number of processes\n";
    	return 0;
    }

    // Declare n processes struct to store info about processes
    processes process[n];

    // Stores burst time of each process 
    int execut[n];

    // Stores number of errors in user input
    int err=0;
    for(int i = 0; i < n; i++)
    {
        cin >> process[i].id >> process[i].arr_time >> process[i].burst_time;

        // Check if arrival or burst time is negative
        if(process[i].arr_time < 0 or process[i].burst_time < 0) err++;

        // Store burst time in this array
        execut[i]=process[i].burst_time;
    }

    // Take user input for time instant
    cin>>inst;

    //  Print the error for invalid process information
    if(err)
    {
    	cout<<"[-]"<<err<<" invalid data provided for arrival and burst time\n";
    	return 0;
    }

    // Check for invalid time instance
    if(inst < 0)
    {
    	cout<<"[-]Negative time not allowed!\n";
    	return 0;
    }

    // Ready queue for scheduling processes
    queue<int> rq;

    // stores completion time of each process
    int completed[n]={0};

    // Stores starting time of execution of each process initialised to -1
    int started[n];
    for(int i=0;i<n;i++) started[i]=-1;

    // Stores current time
    int time = 0;

	// Check if ith process is inside ready queue
    int inside[n]={0};

    // Number of finished processes
    int finished=0;

    // Dummy variables to store time quantum
    int _d1=d1,_d2=d2;

    // Ids of process being executed by Processor1 and Processor2
    int idx1=-1,idx2=-1;

    // Flag to check if time instance has been reached and value is printed or not
    int printed=0;

    // Iterate over all time
    for(time = 0; 1; time++)
    {
    	
    	/*
    	cout<<time<<" ";
    	cout<<"Burst Time is ";
    	for(int j=0;j<7;j++) cout<<process[j].burst_time<<" ";
    	cout<<endl;
    	*/
    	//if(time > 70) break;

    	// Check if ith process can enter into ready queue
    	for(int i=0;i<n;i++)
    	{
    		if(inside[i] or completed[i]>0) continue;
    		if(process[i].arr_time > time) continue;
    		rq.push(i);
    		inside[i]=1;
    	}
    	
    	// Select the process to be executed by processor 1
    	if(_d1==d1)
    	{
    		if(!rq.empty())
    		{
	    		idx1=rq.front();
	    		rq.pop();
    		}
    	}

    	// Select process to be executed by Processor 2
    	if(_d2==d2)
    	{
    		if(!rq.empty())
    		{
    			idx2=rq.front();
    			rq.pop();
    		}
    	}

    	// Print all data if time has reached time instance and break , since we don't need have further thing to do
    	if(time==inst)
    	{
    		printed=1;
    		cout<<"Details of job scheduled at time instant "<<inst<<endl;
    		for(int i=0;i<n;i++)
    		{
    			cout<<process[i].id<<" "<<process[i].arr_time<<" "<<execut[i]<<" ";
    			if(started[i]==-1) cout<<"  ";
    			else cout<<started[i]<<" ";
    			if(completed[i]==0) cout<<"  ";
    			else cout<<completed[i]<<" ";
    			if(completed[i] > 0) cout<<"C ";
    			else if(idx1==i or idx2==i) cout<<"E ";
    			else cout<<"W ";
    			cout<<endl;
    		}
    		cout<<endl;
    		break;
    	}
    	//cout<<idx1<<" "<<idx2 <<endl;

    	// Flag variable to check if current processes need to be pushed at end of queue
    	int psh1=0,psh2=0;

    	// Processor1 executes only if time quantum is remaining and valid process is selected
    	if(_d1 > 0 and idx1 >= 0)
    	{
    		// Store the staring time 
    		if(started[idx1]==-1) started[idx1]=time;

    		// Decrease the burst time
    		process[idx1].burst_time--;

    		// Decrease the dummy time quantum
    		_d1--;

    		// If process completed, store its completion time
    		if(process[idx1].burst_time == 0)
    		{
    			completed[idx1]=time+1;
    			finished++;
    			if(finished==n) break;
    			_d1=d1;
    			idx1=-1;
    		}

    		// If time quantum finished, continue again
    		if(_d1==0)
    		{
    			_d1=d1;
    			psh1=1;
    		}
    	}

    	// Similar to above 
        if(_d2 > 0 and idx2>=0)
        {
        	if(started[idx2]==-1) started[idx2]=time;
        	process[idx2].burst_time--;
        	_d2--;
        	if(process[idx2].burst_time == 0)
        	{
        		completed[idx2]=time+1;
        		finished++;
    			if(finished==n) break;
        		_d2=d2;
        		idx2=-1;
        	}
        	if(_d2==0)
        	{
        		_d2=d2;
        		psh2=1;
        	}
        }

        // If needs to be pushed to end of queue, push it
        if(psh1) rq.push(idx1);
        if(psh2) rq.push(idx2);

    }

    // Check if time instance has not reached and not printed
    if(!printed)
    {
    	cout<<"[-]Invalid time instance provided\n";
    }
    // for(int i=0;i<n;i++) cout<<started[i]<<" "<<completed[i]<<"\n";
    // cout<<endl;
    return 0;
}


/*

Sample Input 
5
10
7
A 0 18
B 0 12
C 0 7
D 0 11
E 0 28
F 7 18
G 16 12
53

*/