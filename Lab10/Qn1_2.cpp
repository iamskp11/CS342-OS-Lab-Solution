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

// Global variables 
int frames,page;        // number of frames and the page numbers, respectively
vector<int> curr;       // stores the reference string 

// Print all necessary informations about current algo
void print(int frames)
{
    cout<<"LRU : \n";
    for(int pg : curr)
    {
        cout<<pg<<" ";
    }
    cout<<"\n";
    cout<<"\nFrame content at each time step t\n";
    for(int i=1;i<=frames;i++) cout<<"F"<<i<<"   ";
    cout<<"\n";
    for(int i=1;i<=frames;i++) cout<<"X    ";
    cout<<"at time = 0\n";
}

// Print the frames at current time
void print_curr(vector<int> &rep,int time)
{
    for(int pgs: rep)
    {
        if(pgs==-1) cout<<"X";
        else cout<<pgs;
        cout<<"    ";
    }
    cout<<"at time = "<<time<<"\n";
}


// driver function
void lru()
{
    int last=0;
    vector<int> last_used(frames,-1);   // stores the time at which page in ith frame was used last
    set<int> inside;                    // stores all the pages which are present currently in frames
    vector<int> rep(frames,-1);       
    int faults=0,time=0;
    for(int pgs : curr)
    {
        //if(last==frames) last=0;
        time++;

        // If page hit, update the last used time and print
        if(inside.count(pgs)) 
        {
            int idx=-1;
            for(int i=0;i<frames;i++)
            {
                    if(rep[i]==pgs) 
                    {
                        idx=i;
                        break;
                    }
            }
            last_used[idx]=time;
            print_curr(rep,time);
        }
        else 
        {

            // If empty frames, put page in it
            if(last<frames)
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
                for(int i=0;i<frames;i++)
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
            print_curr(rep,time);
        }
    }
    cout<<"\n#Faults : "<<faults<<"\n";
    
    cout<<"---------------------------------\n---------------------------------\n";
}

int main()
{
    cout<<"\n\n---------------------------\n";
    int nums=1;
    ifstream in("pages.txt");
    while(in >> frames)
    {
        cout<<"Try #"<<nums<<"\n\n";
        curr.clear();
        while(in >> page)
        {
                if(page==-1) break;
                curr.pb(page);
        }
        print(frames);
        lru();
        cout<<"\n\n";
        nums++;
    }
    return 0;
}