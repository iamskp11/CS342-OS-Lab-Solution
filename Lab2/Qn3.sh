#!/bin/bash
#Author : Saubhik

two_xor()    #finds xor of two numbers
{
  a=$1
  b=$2
  ans=0
  pw=1
  count=0
  limit=1
  
  
  while [ $((a+b)) -ge $limit ];    # I don't know why but semicolon is necessary
  do
      first=$((a%2))
      second=$((b%2))
      if [ $first -eq 1 -a $second -eq 0 ]
	      then
		      ans=$((pw + ans))
		      else 
			      if [ $first -eq 0 -a $second -eq 1 ]
			      then
			      ans=$((pw + ans))
	      fi
      fi
      
     pw=$((pw*2))
     a=$((a/2))
     b=$((b/2))
     count=$((count+1))
     
	  if [ $count -ge 10 ]
		  then
		  break
	  fi
  done
  echo Xor of $1 and $2 is $ans
}

n=$1
m=$2

two_xor $n $m

