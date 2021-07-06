#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

void plot(vector<double> &coord_x, vector<double> &coord_y, string name){
    int cnt_points = coord_x.size(), cnt_commands = 3;
    name =  "\"" + name + "\"";
    name = "set title " + name;
    char * title = new char [name.length()+1];
    strcpy (title, name.c_str());
    char * commands[10000];
    commands[0] = title;
    commands[1] = "set xlabel \"Seek time (ms)\"";
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
    fprintf(temp, "%lf %lf \n", coord_x[i], coord_y[i]); //Write the data to a temporary file
    
    for (int i=0; i < cnt_commands; i++)
      fprintf(gnu_plot_pipe, "%s \n", commands[i]); //Send commands to gnuplot one by one.
}

int main()
{
  vector<double> x={51,48,47};
  vector<double> y={-1,-2,-3};
  plot(x,y,"FIFO");
  return 0;
}