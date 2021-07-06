#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <math.h>


pthread_t thread_id[4];
int n,m;
int A[100][100], B[100][100],C[100][100];
/*

Thread 1 will check Commutative Law and prints the output as “Commutative”.
● Thread 2 will check Associative Law and prints the output as “Associative”.
● Thread 3 will check Additive Identity and prints the Additive Identity Matrix as
output.
● Thread 4 will check Additive Inverse and prints the Additive Inverse Matrix as
output.

*/

void * Commut(void * arr)
{

   	int D[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			D[i][j]=A[i][j]+B[i][j];
   		}
   	}
   	
   	int E[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			E[i][j]=B[i][j]+A[i][j];
   		}
   	}
   	
   	int errors=0;
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			if(D[i][j] != E[i][j]) errors++;
   		}
   	}
   	
   	if(errors==0) printf("Commutative property is true\n");\
   	else printf("Commutative property fails\n");
    pthread_exit(NULL);
}

void * Assoc(void * arr)
{

   	int D[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			D[i][j]=(A[i][j]+B[i][j])+C[i][j];
   		}
   	}
   	
   	int E[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			E[i][j]=A[i][j]+(B[i][j]+C[i][j]);
   		}
   	}
   	
   	int errors=0;
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			if(D[i][j] != E[i][j]) errors++;
   		}
   	}
   	
   	if(errors==0) printf("Associative property is true\n");
   	else printf("Associative property fails\n");
    pthread_exit(NULL);
}

void * AddIden(void * arr)
{

   	int IdentityMatrix[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			IdentityMatrix[i][j]=0;
   		}
   	}
   	
   	int D[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			D[i][j]=A[i][j]+IdentityMatrix[i][j];
   		}
   	}
   	
   	int E[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			E[i][j]=IdentityMatrix[i][j]+A[i][j];
   		}
   	}
   	
   	int errors=0;
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			if(D[i][j] != E[i][j]) errors++;
   		}
   	}
   	
   	if(errors==0) printf("Identity property is true\n");\
   	else printf("Identity property fails\n");
   	printf("Additive Identity Matrix of A matrix is : \n");
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			printf("%d ",IdentityMatrix[i][j]);
   		}
   		printf("\n");
   	}
    pthread_exit(NULL);
}

void * AddInv(void * arr)
{

   	int InverseMatrix[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			InverseMatrix[i][j]=-A[i][j];
   		}
   	}
   	
   	int D[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			D[i][j]=A[i][j]+InverseMatrix[i][j];
   		}
   	}
   	
   	int E[n][m];
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			E[i][j]=InverseMatrix[i][j]+A[i][j];
   		}
   	}
   	
   	int errors=0;
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			if(D[i][j] != E[i][j] || E[i][j]!=0) errors++;
   		}
   	}
   	
   	if(errors==0) printf("Additive Inverse property is true\n");\
   	else printf("Additive Identity property fails\n");
   	printf("Additive Inverse Matrix of Matrix A is : \n");
   	for(int i=0;i<n;i++)
   	{
   		for(int j=0;j<m;j++)
   		{
   			printf("%d ",InverseMatrix[i][j]);
   		}
   		printf("\n");
   	}
    pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
    printf("Enter the dimenstions (n X m) of the matrices : ");
    scanf("%d%d",&n,&m);
    printf("Enter matrix A of dimension %d X %d :\n",n,m);
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		scanf("%d",&A[i][j]);
    	}
    }
    printf("Enter matrix B of dimension %d X %d :\n",n,m);
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		scanf("%d",&B[i][j]);
    	}
    }
    printf("Enter matrix C of dimension %d X %d :\n",n,m);
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		scanf("%d",&C[i][j]);
    	}
    }
    pthread_create(&thread_id[0], NULL, Commut, NULL);
    pthread_create(&thread_id[1], NULL, Assoc, NULL);
    pthread_create(&thread_id[2], NULL, AddIden, NULL);
    pthread_create(&thread_id[3], NULL, AddInv, NULL);
   // pthread_join(thread_id[i],&ret);   // receive return value ((void)static int) in ret variable
    
    pthread_exit(NULL);
}

