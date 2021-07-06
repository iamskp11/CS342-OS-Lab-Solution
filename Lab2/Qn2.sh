#!/bin/bash
#Author : Saubhik


fact()     #finds factorial of a number
{
  num=$1
  
  if [ $num -le 1 ]
	  then
	  	echo $num
	  else 
		  prev=$(fact $(($1-1)))
		  x=$((prev * num))
		  echo $x
  fi
}


is_prime ()     #checks if number is prime or not , returns 1 if prime is 1
{
   num=$1
   if [ $num -le 1 ]
	   then
		   echo 0
		   exit
   fi
   
   for((i=2;i<=num/2;i++))
      do
	  if [ $((num%i)) -eq 0 ]
		  then
			    return 0
			    exit
	  fi
      done
      
   return 1
}



PrimeNoLessThan()   #sums all primes below n
{
   num=$1
   is_prime $1
   res=$?
   
   if [ $res -eq 0 ]
	   then
	   	if [ $1 -eq 1 ]    #space must between ends of brackets
		   then
		   	echo 0
		   else
		   	echo $(PrimeNoLessThan $(($1-1)))
	   fi
	   else 
		   prev=$(PrimeNoLessThan $(($1-1)))
		   echo $((num + prev))
   fi
 

}




n=$1
echo $(($(PrimeNoLessThan $n) * $(fact $n)))



