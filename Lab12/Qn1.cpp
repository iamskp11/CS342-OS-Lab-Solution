#include <bits/stdc++.h>
using namespace std;

#define pb push_back

/*
FIFO
SCAN
C_SCAN
SSTF
*/


// Standard algo to plot 2D graph
void plot(vector<int> &x, string name){
	int len=x.size();
	vector<double> coord_y,coord_x;
	for(int i=0;i<len;i++) coord_x.pb(x[i]*1.0);
	for(int i=1;i<=len;i++) coord_y.pb(1.0*i);
    int cnt_points = coord_x.size(), cnt_commands = 3;
    name =  "\"" + name + "\"";
    name = "set title " + name;
    char * title = new char [name.length()+1];
    strcpy (title, name.c_str());
    char * commands[10000];
    commands[0] = title;
    commands[1] = "set xlabel \"Order of Query\"";
    commands[2] = "set ylabel \"#Cylinders\"";
    
    for (int i=0; i < cnt_points; i++){
      string tmp= "\"" + to_string(  (int)coord_x[i]) + " " + to_string((int)coord_y[i]) + "\"" ;
      tmp = "set label " + tmp + " at " +  to_string( coord_x[i]) + "," + to_string(coord_y[i]);
      char * label = new char [tmp.length()+1];
      strcpy (label, tmp.c_str());
      commands[ cnt_commands] = label;
      cnt_commands++;
    }
    
    commands[cnt_commands++] = "plot 'data.temp' with linespoints";
    	FILE * temp = fopen("data.temp", "w");
	    FILE * gnu_plot_pipe = popen ("gnuplot -persistent", "w");
	    for (int i=0; i < cnt_points; i++)
	    {
	    	//cout<<"Into file "<<coord_x[i]<<" "<<coord_y[i]<<endl;
	    	fprintf(temp, "%lf %lf \n", coord_x[i], coord_y[i]);
		}
	    for (int i=0; i < cnt_commands; i++)
	      fprintf(gnu_plot_pipe, "%s \n", commands[i]); 
	  fclose(temp);
	  fclose(gnu_plot_pipe);
}


// Store info about algo and head movement taken
struct info
{
		string algo;
		int hm;
};

// FIFO ~ FCFS Algo
vector<int> FIFO(vector<int>& req,int curr)
{
	int hm=0;
	int n=req.size();
	vector<int> d;
	d.pb(curr);
	for(int disc: req)
	{
		//hm+=abs(curr-disc);
		curr=disc;
		d.pb(curr);
	}
	return d;
}

// SCAN Algo
vector<int> SCAN(vector<int>& req,int curr,int cyl)
{
	// The head moves to larger end first (cyl-1), and then reverse to smaller end(0)
	int hm=0;
	int n=req.size();
	vector<int> d;
	d.pb(curr);
	vector<int> larger,smaller;
	for(int disc : req)
	{
		if(disc>=curr) larger.pb(disc);
		else smaller.pb(disc);
	}
	sort(larger.begin(),larger.end());
	sort(smaller.rbegin(), smaller.rend());
	for(int disc : larger)
	{
		hm+=abs(curr-disc);
		curr=disc;
		d.pb(curr);
	}
	if(curr!=cyl-1)
	{
		d.pb(cyl-1);
		curr=cyl-1;
		hm+=(cyl-1-curr);
	}
	for(int disc : smaller)
	{
		hm+=abs(disc-curr);
		curr=disc;
		d.pb(curr);
	}
	return d;
}


// C-SCAN Algo
vector<int> C_SCAN(vector<int>& req,int curr,int cyl)
{
	// The head moves to larger end first (cyl-1), and then reverse to smaller end(0)
	int hm=0;
	int n=req.size();
	vector<int> d;
	d.pb(curr);
	vector<int> larger,smaller;
	for(int disc : req)
	{
		if(disc>=curr) larger.pb(disc);
		else smaller.pb(disc);
	}
	sort(larger.begin(),larger.end());
	sort(smaller.begin(), smaller.end());
	for(int disc : larger)
	{
		hm+=abs(curr-disc);
		curr=disc;
		d.pb(curr);
	}
	if(curr!=cyl-1)
	{
		d.pb(cyl-1);
		curr=cyl-1;
		hm+=(cyl-1-curr);
	}
	curr=0;
	hm+=cyl-1;
	d.pb(0);
	for(int disc : smaller)
	{
		if(disc==0) continue;
		hm+=abs(disc-curr);
		curr=disc;
		d.pb(curr);
	}
	return d;
}

// SSTF Algo
vector<int> SSTF(vector<int>& req,int curr)
{
	//cout<<"Error here\n";
	int hm=0;
	int n=req.size();
	vector<int> d;
	d.pb(curr);
	vector<int> vis(n,0);
	while(1)
	{
		int nearest=INT_MAX,idx=-1;
		for(int i=0;i<n;i++)
		{
			if(vis[i]) continue;
			int move=abs(req[i]-curr);
			if(move<nearest)
			{
					idx=i;
					nearest=move;
			}
		}
		if(idx==-1) break;
		vis[idx]=1;
		curr=req[idx];
		hm+=nearest;
		d.pb(curr);
	}
	//cout<<d[0]<<endl;
	return d;
}


// Counts total head movements
int countHM(vector<int> req)
{
	int n=req.size();
	int ret=0;
	for(int i=1;i<n;i++) ret+=abs(req[i]-req[i-1]);
	return ret;
}

// Custom sort function to sort info struct
bool compare(info a,info b)
{
	return a.hm>b.hm;
}

int main()
{
		cout<<"Number of cylinders : ";
		int cyl;
		cin>>cyl;
		cout<<"Current Head Position : ";
		int curr;
		cin>>curr;
		cout<<"Enter Number of requests : ";
		int tot;
		cin>>tot;
		cout<<"Enter Request Queue : ";
		vector<int> req(tot,0);
		for(int i=0;i<tot;i++) cin>>req[i];
		vector<int> fifo=FIFO(req,curr);
		vector<int> scan=SCAN(req,curr,cyl);
		vector<int> c_scan=C_SCAN(req,curr,cyl);
		vector<int> sstf=SSTF(req,curr);
		int hm_fifo=countHM(fifo);
		int hm_scan=countHM(scan);
		int hm_cscan=countHM(c_scan);
		int hm_sstf=countHM(sstf);
		info data[4];
		data[0].algo="FIFO",data[0].hm=hm_fifo;
		data[1].algo="SCAN",data[1].hm=hm_scan;
		data[2].algo="C_SCAN",data[2].hm=hm_cscan;
		data[3].algo="SSTF",data[3].hm=hm_sstf;
		sort(data,data+4,compare);
		cout<<"\nSorting order : Worst Seeking Time first\n\n";
		for(int i=0;i<4;i++)
		{
			cout<<"Algo : "<<data[i].algo<<"\n"<<"Total Head Movements : "<<data[i].hm<<"\n"<<"Seek Time : "<<data[i].hm*5<<"ms\n\n";

			// Plot the graphs as per algo
			string al=data[i].algo;
			if(al=="FIFO") plot(fifo,al);
			if(al=="SCAN") plot(scan,al);
			if(al=="C_SCAN") plot(c_scan,al);
			if(al=="SSTF") plot(sstf,al);
			
		}
		return 0;
}