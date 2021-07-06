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


int main()
{
	cout<<"Part 1\n";
	int c,r;
	cout<<"Enter c and r : ";
	cin>>c>>r;
	int n=(r-1)/(c-1);
	cout<<"Maximum value of n to ensure deadlock free execution : "<<n<<endl;

	cout<<"Part 2\n";
	cout<<"Enter number of processes : ";
	cin>>n;
	cout<<"Enter copies/needs for each process \n";
	vector<int> copies(n,0);
	for(int i=0;i<n;i++) cin>>copies[i];
	int maxi_resource=0;
    for(int copy : copies)
    {
    		maxi_resource+=(copy-1);
    }
	cout<<"Maximum copies of r for not gauranteed deadlock free operation : "<<maxi_resource<<endl;
	cout<<"Minimum copies of r for gauranteed deadlock free operation : "<<maxi_resource+1<<endl;
	return 0;
}