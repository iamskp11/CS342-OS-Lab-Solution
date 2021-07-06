#!/bin/sh
#Author : Saubhik


#function to check if numbers are valid and also iterate if possible
fn()
{
   a=$1
   b=$2
   if [ $a -gt $b ]
	   then
	   	echo Can not iterate in reverse
	   else 
		   while [ $a -le $b ]     # while loop
			   do
				   echo "$a \c" 
				   a=`expr $a + 1`
			   done
   fi
}

#check for appropriate arguments
a=2
if [ $# -eq $a ]
	then
		fn $1 $2
	else 
		echo Give 2 arguments only
fi

#  To execute
#  command must be ./Qn2.sh (number)  (number)
#   both numbers can be any integer and without brackets
#
#
#
#
