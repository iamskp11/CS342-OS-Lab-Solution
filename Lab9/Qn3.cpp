/*
   Banker's Algo Implementation
*/

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
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vll vector<vector<ll>>
#define ms(a, v) memset(a, v, sizeof(a))
#define sortv(a) sort(a.begin(), a.end())
#define range(i, a, b, c) for (int i = a; i < b; i += c)
#define inf 10000000000000000

void all_input()
{
#ifndef ONLINE_JUDGE
    freopen("inputf.in", "r", stdin);
    freopen("outputf.in", "w", stdout);
#endif
}

int n, r;
int freq = 0;

// Recursive function to find the safe sequence
void solve(vector<int> avail, vector<vector<int>> need, vector<vector<int>> alloc, vector<int> finish, vector<int> seq)
{
    for (int i = 0; i < n; i++)
    {
        if (finish[i])
            continue;
        int poss = 1;
        for (int j = 0; j < r; j++)
        {
            if (need[i][j] > avail[j])
            {
                poss = 0;
                //break;
            }
        }
        if (!poss)
            continue;

        for (int j = 0; j < r; j++)
            avail[j] += alloc[i][j];
        finish[i] = 1;

        seq.pb(i);
        solve(avail, need, alloc, finish, seq);
        finish[i] = 0;
        seq.pop_back();
        for (int j = 0; j < r; j++)
            avail[j] -= alloc[i][j];
    }
    
    // It is a  safe sequence if resources are successfully allocated to all processes
    if (seq.size() == n)
    {
        freq++;
        cout << "Safe Sequence " << freq << " : ";
        for (int i = 0; i < n; i++)
        {
            cout << seq[i];
            if (i < n - 1)
                cout << "--> ";
        }
        cout << endl;
    }
}

int main()
{
    //all_input();
    cout << "Enter number of processes : ";
    cin >> n;
    cout << "Enter number of resources : ";
    cin >> r;
    vector<int> tot(r, 0);
    for (int i = 0; i < r; i++)
    {
        cout << "Enter total amount of resources" << i + 1 << " : ";
        cin >> tot[i];
    }
    vector<vector<int>> maxM(n, vector<int>(r, 0));
    cout << "Enter the max matrix\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " ";
        for (int j = 0; j < r; j++)
            cin >> maxM[i][j];
    }

    vector<vector<int>> alloc(n, vector<int>(r, 0));
    cout << "Enter the allocation matrix\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " ";
        for (int j = 0; j < r; j++)
            cin >> alloc[i][j];
    }

    vector<vector<int>> need(n, vector<int>(r, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
            need[i][j] = maxM[i][j] - alloc[i][j];
    }
    vector<int> avail(r, 0);
    for (int i = 0; i < r; i++)
    {
        int init = tot[i];
        for (int j = 0; j < n; j++)
            init -= alloc[j][i];
        avail[i] = init;
    }
    vector<int> finish(n, 0), seq;
    cout << endl;
    solve(avail, need, alloc, finish, seq);
    if (freq == 0)
        cout << "No Safe Sequence found\n";
    return 0;
}
