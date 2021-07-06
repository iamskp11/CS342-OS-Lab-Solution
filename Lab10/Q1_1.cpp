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


// global variables
int frames,page;   // number of frames and page 
vector<int> curr;  // stores all the pages 


// print the info about algo
void print(int frames)
{
    cout<<"FIFO : \n";
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


// Print current state of frame
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
void fifo()
{
    int last=0;     // index of frame to be removed if page fault occurs
    set<int> inside;  // stores all current pages in frame
    vector<int> rep(frames,-1);   // current state of frame
    int faults=0,time=0;
    for(int pgs : curr)
    {
        // reorder last pointer if it goes out of bound
        if(last==frames) last=0;
        time++;

        // if page hit, simply print current state
        if(inside.count(pgs)) 
        {
            print_curr(rep,time);
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
            print_curr(rep,time);
        }
    }
    cout<<"\n#Faults : "<<faults<<"\n";
    
    cout<<"---------------------------------\n---------------------------------\n";
}


int main()
{
    cout<<"-----------------------------------\n";
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
        fifo();
        cout<<"\n\n";
        nums++;
    }
    return 0;
}