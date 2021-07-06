#!/bin/sh
#Author : Saubhik

#function to reverse the integer
fn()
{
   lowest=0
   num=$1
   ans=0
   neg=0
   if [ $neg -gt $num ]
	   then 
		   neg=1
		   num=`expr $num \* -1`
   fi
   
   
   while [ $num -gt $lowest ]
	   do 
		   x=10
		   val=`expr $num % $x`
		   num=`expr $num / 10 `
		   ans=`expr $ans \* 10 + $val`
	   done
   if [ $neg -eq 1 ]
	   then
	   	ans=`expr $ans \* -1`
   fi
   echo $ans
}

#check for appropriate number of arguments
a=1
if [ $# -eq $a ]
	then 
		fn $1
	else 
		echo Please enter 1 argument only
fi



#  To execute
#  command must be ./Qn1.sh (number)  
#   number can be any integer and without brackets
#
#
#
#

