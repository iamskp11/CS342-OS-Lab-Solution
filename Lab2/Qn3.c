#include <stdio.h>
#include <time.h>

int two_xor(int a,int b)
{
   int ans=0,pw=1;
   while(a>0 || b>0)
   {
      if( (a+b)%2 ) ans+=pw;
      pw*=2;
      a/=2,b/=2;
   }
   return ans;
}

int main()
{
   clock_t start=clock();
   int a,b;
   printf("Enter two numbers : ");
   scanf("%d%d",&a,&b);
   int ans=two_xor(a,b);
   printf("\nXor of %d and %d is %d\n",a,b,ans);
   clock_t end=clock();
   double tot_time=(double)(end-start)/CLOCKS_PER_SEC;
   printf("\nTotal time taken is %f s\n",tot_time);
}
