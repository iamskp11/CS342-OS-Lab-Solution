#include <bits/stdc++.h>
using namespace std;

#define pb push_back


// Standard Function to plot a 2D graph
void plot(vector<int> &x, vector<double> &coord_x,string name){
	int len=x.size();
	vector<double> coord_y;
	for(int i=0;i<len;i++) coord_y.pb(x[i]*1.0);
	//for(int i=1;i<=len;i++) coord_y.pb(1.0*i);
    int cnt_points = coord_x.size(), cnt_commands = 3;
    name =  "\"" + name + "\"";
    name = "set title " + name;
    char * title = new char [name.length()+1];
    strcpy (title, name.c_str());
    char * commands[10000];
    commands[0] = title;
    commands[1] = "set xlabel \"#Cylinders\"";
    commands[2] = "set ylabel \"Order of Query\"";
    
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
	    	fprintf(temp, "%lf %lf \n", coord_x[i], coord_y[i]); //Write the data to a temporary file
		}
	    for (int i=0; i < cnt_commands; i++)
	      fprintf(gnu_plot_pipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
	  fclose(temp);
	  fclose(gnu_plot_pipe);
}

// Driver algorithm
void s_look(vector<int> &req,int curr,int cyl)
{
		vector<int> smaller,larger;
		// FInd minimum request cylinder and maximum request cylinder
		int mini=INT_MAX,maxi=-1;
		for(int disc : req)
		{
			mini=min(mini,disc);
			maxi=max(maxi,disc);
		}
		// If right is less far, go to right
		// else go to left
		if(abs(curr-maxi)<abs(curr-mini)) 
		{
				for(int disc : req)
				{
					if(disc<curr) larger.pb(disc);
					else smaller.pb(disc);
				}
				sort(smaller.begin(), smaller.end());
				sort(larger.rbegin(), larger.rend());
		}
		else
		{
				for(int disc : req)
				{
					if(disc>curr) larger.pb(disc);
					else smaller.pb(disc);
				}
				sort(smaller.rbegin(), smaller.rend());
				sort(larger.begin(), larger.end());
		}
        
		
		int hm=0;
		double stime=0;
		vector<int> d;
		vector<double> seek_time;
		d.pb(curr);
		seek_time.pb(0);
		for(int disc : smaller)
		{
			//cout<<disc<<endl;
			hm+=abs(curr-disc);
			stime+=abs(curr-disc)*5.0;
			curr=disc;
			d.pb(curr);
			seek_time.pb(stime);
		}
		for(int disc : larger)
		{
			//cout<<disc<<endl;
			hm+=abs(curr-disc);
			stime+=abs(curr-disc)*5.0;
			curr=disc;
			d.pb(curr);
			seek_time.pb(stime);
		}
		// Plot graph
		plot(d,seek_time,"S-LOOK");
		cout<<"\nTotal Head Movements : "<<hm<<endl;
		cout<<"Total Seek Time : "<<hm*5<<"ms"<<endl;
		return ;
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
		s_look(req,curr,cyl);
		return 0;
}