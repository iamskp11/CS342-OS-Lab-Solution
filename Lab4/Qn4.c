#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


#define MAX_LEN 100

// Sorts an array of strings where length of every
// string should be smaller than MAX_LEN
void selectionSort(char arr[][MAX_LEN], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	char minStr[MAX_LEN];
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		int min_idx = i;
		strcpy(minStr, arr[i]);
		for (j = i+1; j < n; j++)
		{
			// If min is greater than arr[j]
			if (strcmp(minStr, arr[j]) > 0)
			{
				// Make arr[j] as minStr and update min_idx
				strcpy(minStr, arr[j]);
				min_idx = j;
			}
		}

		// Swap the found minimum element with the first element
		if (min_idx != i)
		{
			char temp[MAX_LEN];
			strcpy(temp, arr[i]); //swap item[pos] and item[i]
			strcpy(arr[i], arr[min_idx]);
			strcpy(arr[min_idx], temp);
		}
	}
}



int main() {
FILE *file1;
file1=fopen("file1.txt","r");
FILE *file2,*file3;
file2=fopen("file2.txt","w");
file3=file2;
int type=1;
char c;
file3=fopen("file1.txt","r");
    while((c=fgetc(file3))!=EOF)
    {
       if(c==9 || c=='\n') continue;
       if(c<48 || c>57) 
       {
       	type=2 ;
       	break;
       }
    } 

    pid_t pid1;
    pid1=fork();
    
    if(pid1==0)//child1
    {   
      
          pid_t pid2;
          
          pid2=fork();
          
          if(pid2==0)//child2---1
          {   
          
            printf("\nGoing to copy the content of file1 to file2 \n");
            printf("(Child 1)::My process id is %d and the parent of my process has id %d\n",getpid(),getppid());
            
            char chunk[100];
            while(fgets(chunk,sizeof(chunk),file1)!=NULL)
            {
            	fprintf(file2,"%s",chunk);
            } 
            printf("!!Copied Successfully!!\n");
            
        
          }
          else//child1-----2
          {
              wait(NULL);
             
                printf("\n(Child 2) :: My process id is %d and the parent of my process has id %d\n",getpid(),getppid());
                  printf("Going to display the content of file2 \n");
                printf("Here are the contents of file2\n");
        
        	char c;
        	file3=fopen("file2.txt","r");
		    while((c=fgetc(file3))!=EOF)
		    {
		       printf("%c",c);
		    } 
		printf("\n!!!Content Shown Successfully!!!\n");
            
          }
    }
    else//parent
    {
       wait(NULL);
       pid_t pid3;
       pid3=fork();
       if(pid3==0)//child3-----3
       {
         printf("\nGoing to display the sorted content of file2 in reverse order \n");
          printf("(Child 3) :: My process id is %d and the parent of my process has id %d\n",getpid(),getppid());
        
        char arr[100][100];
        file3=fopen("file2.txt","r");
        char word[50];
        int i=0;
        while (fscanf(file3, "%s", word) != EOF)
        {
            strcpy(arr[i],word);
            i++;
        }
      
      	
       if(type==1) printf("\nIt is integer aray\n");
       else printf("\nIt is string array\n");
       printf("\nElements in reverse sorted order are \n");
       if(type==2)
       {
        selectionSort(arr,i);
        for(int j=i-1;j>=0;j--) printf("%s\n",*(arr+j));
       }
       else 
       {
         int num[100];
         for(int j=0;j<i;j++) num[j]=atoi(arr[j]);
         for(int j=0;j<i-1;j++)
         {
         	for(int k=0;k<i-j-1;k++)
         	{
         		if(num[k]>num[k+1])
         		{
         		   int temp=num[k];
         		   num[k]=num[k+1];
         		   num[k+1]=temp;
         		}
         	}
         }
         for(int j=i-1;j>=0;j--) printf("%d\n",num[j]);
       }
       }
       else//parent
       {    wait(NULL);
           printf("\nI am the PARENT process with process id %d \n",getpid());
       
       }
       
        
        
    }
        
}


