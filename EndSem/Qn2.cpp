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


double t_lpf=0,t_lru=0,t_fifo=0;
// Least Page Fault Algorithm
int LPF(int f,int n,vector<int>& curr)
{
	clock_t start = clock();
	vector<int> frames(f,-1);
	set<int> st;
	int faults=0,last=0;
	map<int,int> page_faults;
	for(int i=0;i<n;i++)
	{
		int page=curr[i];
		if(st.count(page)==0)
		{
			if(last!=f)
			{
				//cout<<"Inserting in "
				frames[last]=page;
				last++;
			}
			else 
			{
				int idx=-1,mini=INT_MAX;
				for(int j=0;j<f;j++)
				{
					int here=frames[j];
				    if(mini>page_faults[here])
				    {
				    	mini=page_faults[here];
				    	idx=j;
				    }
				}
				//cout<<"Removing "<<idx<<" "<<frames[idx]<<endl;
				st.erase(st.find(frames[idx]));
				frames[idx]=page;
			}
			page_faults[page]++;
			st.insert(page);
			faults++;
		}
	}
	clock_t end = clock();
	t_lpf+=double(end - start)/CLOCKS_PER_SEC;
	return faults;
}

int FIFO(int f,int n,vector<int>& curr)
{
	clock_t start = clock();
    int last=0;     // index of frame to be removed if page fault occurs
    set<int> inside;  // stores all current pages in frame
    vector<int> rep(f,-1);   // current state of frame
    int faults=0,time=0;
    for(int pgs : curr)
    {
        // reorder last pointer if it goes out of bound
        if(last==f) last=0;
        time++;

        // if page hit, simply print current state
        if(inside.count(pgs)) 
        {
            continue;
        }
        else 
        {
            // check if there is any empty frame
            int pre=rep[last];
            if(pre==-1) 
            {
                // if empty, put the page there
                rep[last]=pgs;
                inside.insert(pgs);
                last++;
            }
            else 
            {
                // erase the page , and put current page there
                rep[last]=pgs;
                inside.erase(inside.find(pre));
                inside.insert(pgs);
                last++;
            }
            faults++;
        }
    }
    clock_t end = clock();
	t_fifo+=double(end - start)/CLOCKS_PER_SEC;
    return faults;
}

int LRU(int f,int n,vector<int>& curr)
{
	clock_t start = clock();
    int last=0;
    vector<int> last_used(f,-1);   // stores the time at which page in ith frame was used last
    set<int> inside;                    // stores all the pages which are present currently in frames
    vector<int> rep(f,-1);       
    int faults=0,time=0;
    for(int pgs : curr)
    {
        //if(last==frames) last=0;
        time++;

        // If page hit, update the last used time and print
        if(inside.count(pgs)) 
        {
            int idx=-1;
            for(int i=0;i<f;i++)
            {
                    if(rep[i]==pgs) 
                    {
                        idx=i;
                        break;
                    }
            }
            last_used[idx]=time;
        }
        else 
        {

            // If empty frames, put page in it
            if(last<f)
            {
                rep[last]=pgs;
                inside.insert(pgs);
                last_used[last]=time;
                last++;
            }
            else 
            {
                // find which page has minimum last_used time
                int mini_time=INT_MAX,idx=-1;
                for(int i=0;i<f;i++)
                {
                    if(last_used[i] < mini_time)
                    {
                        mini_time=last_used[i];
                        idx=i;
                    }
                }
                int to_remove=rep[idx];
                rep[idx]=pgs;
                last_used[idx]=time;
                inside.erase(inside.find(to_remove));
                inside.insert(pgs);
            }
            faults++;
        }
    }
    clock_t end = clock();
	t_lru+=double(end - start)/CLOCKS_PER_SEC;
    return faults;
}

// Print all list of number of faults
void print_all(vector<int>& a)
{
	for(int p: a) cout<<p<<" ";
		cout<<endl;
}
int main()
{
	int t;
	cout<<"Number of testcases : ";
	cin>>t;
	vector<int> lpf,fifo,lru;
	while(t--)
	{
		cout<<"Number of frames , Number of requests : ";
		int f,n;
		cin>>f>>n;
		cout<<"Enter request queue : ";
		vector<int> curr(n,0);
		for(int i=0;i<n;i++) cin>>curr[i];
		int _lpf=LPF(f,n,curr);
		lpf.pb(_lpf);
		int _fifo=FIFO(f,n,curr);
		fifo.pb(_fifo);
		int _lru=LRU(f,n,curr);
		lru.pb(_lru);
	}
	cout<<"\n Summary \n";
	cout<<"A: ";
	print_all(lpf);
	cout<<"LRU: ";
	print_all(lru);
	cout<<"FIFO: ";
	print_all(fifo);
	cout<<"Time taken\n";
	printf("A: %.8fs LRU: %.8fs FIFO: %.8fs\n",t_lpf,t_lru,t_fifo);
	return 0;
}