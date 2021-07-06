Name - Saubhik Kumar
Roll - 1801CS44
OS Lab
Endsem Examination 

--------------------------------------------------------------------------


Note : I have also attached the pics of the sample I/O and plot in the folder for further reference.

Qn1)
Compile by : g++ Qn1.cpp -o Qn1
Run by : ./Qn1

Sample I/O:

saubhik@saubhik-virtual-machine:~/os_lab/EndSem$ ./Qn1
Part 1
Enter c and r : 2 9
Maximum value of n to ensure deadlock free execution : 8
Part 2
Enter number of processes : 4
Enter copies/needs for each process 
10 12 13 3
Maximum copies of r for not gauranteed deadlock free operation : 34
Minimum copies of r for gauranteed deadlock free operation : 35

Qn2)
Compile by : g++ Qn2.cpp -o Qn2
Run by : ./Qn2

Sample I/O:

saubhik@saubhik-virtual-machine:~/os_lab/EndSem$ ./Qn2
Number of testcases : 1
Number of frames , Number of requests : 3 10
Enter request queue : 1 2 3 4 4 3 2 1 2 3

 Summary 
A: 5 
LRU: 5 
FIFO: 7 
Time taken
A: 0.00001900s LRU: 0.00000500s FIFO: 0.00000600s


Qn3)
Compile by : g++ Qn3.cpp -o Qn3
Run by : ./Qn3

Sample I/O:

saubhik@saubhik-virtual-machine:~/os_lab/EndSem$ ./Qn3
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
Details of job scheduled at time instant 53
A 0 18 0 43 C 
B 0 12 0 24 C 
C 0 7 5 22 C 
D 0 11 10 30 C 
E 0 28 10   E 
F 7 18 20 51 C 
G 16 12 25 52 C 


Qn4)

Note : 
1. Ignore warnings if any. They do not affect program output.
2. Function to plot graph using gnuplot is a standard function (since we are never taught about it).

Compile by : g++ Qn4.cpp -o Qn4
Run by : ./Qn4

Sample I/O:

saubhik@saubhik-virtual-machine:~/os_lab/EndSem$ ./Qn4
Number of cylinders : 200
Current Head Position : 98
Enter Number of requests : 8      
Enter Request Queue : 98 183 37 122 14 124 65 67

Total Head Movements : 253
Total Seek Time : 1265ms


