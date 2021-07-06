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
int frames,page;       // number of frames and the page numbers, respectively
vector<int> curr;      // stores the reference string 


// Print all necessary informations about current algo
void print(int frames)
{
    cout<<"Optimal : \n";
    for(int pg : curr)
    {
        cout<<pg<<" ";
    }
    cout<<"\n\n";
    cout<<"Frame content at each time step t\n";
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
void optimal()
{
    int last=0;
    set<int> inside;
    vector<int> rep(frames,-1);
    int faults=0,time=0;
    for(int k=0;k<curr.size();k++)
    {
        int pgs=curr[k];
        time++;

        // If page hit, simply print and continue
        if(inside.count(pgs)) 
        {
            print_curr(rep,time);
        }
        else 
        {
            // If some empty frames, fill them
            if(last<frames)
            {
                rep[last]=pgs;
                inside.insert(pgs);
                last++;
            }
            else 
            {
                // Find which page is used at last , and find the frame number of that index
                // Frame number is denoted by idx
                int idx=-1;
                map<int,int> first_used;   // stores the time at which page is first used 
                for(int i=k+1;i<curr.size();i++)
                {
                    if(first_used.count(curr[i])) continue;
                    first_used[curr[i]]=i;
                }

                // find the page used at very last
                int maxi=-1;
                for(int i=0;i<frames;i++)
                {
                    if(first_used.count(rep[i])==0)
                    {
                        idx=i;
                        break;
                    }
                    if(first_used[rep[i]] > maxi)
                    {
                        maxi=first_used[rep[i]];
                        idx=i;
                    }
                }
                //  Got whoch idx to remove, then remove it
                int to_remove=rep[idx];
                rep[idx]=pgs;
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
        curr.clear();
        while(in >> page)
        {
                if(page==-1) break;
                curr.pb(page);
        }
        cout<<"Try #"<<nums<<"\n\n";
        print(frames);
        optimal();
        cout<<"\n\n";
        nums++;
    }
    return 0;
}