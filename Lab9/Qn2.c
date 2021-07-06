/*
   Deadlock Detection algo
*/


#include <stdio.h>

int main()

{

int n,r;
printf("Enter total number of processes : ");
scanf("%d",&n);
printf("Enter total number of Resources : ");
scanf("%d",&r);
int tot[r];
for(int i=0;i<r;i++) 
{
	printf("Total number of Resource%d : ",i+1);
	scanf("%d",&tot[i]);
}

printf("Enter Request Matrix : ");
int req[n][r];

for(int i=0;i<n;i++)
{
for(int j=0;j<r;j++) scanf("%d",&req[i][j]);
}


printf("Enter Allocation matrix : ");
int alloc[n][r];

for(int i=0;i<n;i++)
{
for(int j=0;j<r;j++) scanf("%d",&alloc[i][j]);
}

int work[r],finish[n];
for(int i=0;i<n;i++) finish[i]=0;

for(int i=0;i<r;i++)
{
	int busy=0;
    for(int j=0;j<n;j++) if(alloc[j][i]) busy++;
    work[i]=tot[i]-busy;
}

while(1)
{
	int idx=-1;
	for(int i=0;i<n;i++)
	{
	    if(finish[i]) continue;
	    int poss=1;
	    for(int j=0;j<r;j++) 
	    {
	    		if(req[i][j]>work[j]) 
	    		{
	    		poss=0;
	    		break;
	    		}
	    }
	    if(!poss)  continue;
	    idx=i;
	    break;
	}
	if(idx==-1) break;
	finish[idx]=1;
	for(int j=0;j<r;j++) work[j]+=alloc[idx][j];
	
}

int dl=0;
for(int i=0;i<n;i++)  if(!finish[i]) dl=1;
if(dl) printf("Deadlock detected\n");
else printf("No Deadlock detected\n");

return 0;
}
