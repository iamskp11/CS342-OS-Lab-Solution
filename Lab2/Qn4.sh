#!/bin/bash
#Author : Saubhik

#Length – a minimum of 7 characters.
#Contain both alphabet and number.
#Contain one special char ( /, (, ),<, >, ? )




read -p "Enter password : " s
len=${#s}
idx=0

success="Valid Password"
fail="Invalid Password"

if [ $len -lt 7 ]    #checks for minimum length 7
	then
	echo  $fail
	exit
fi


spcls=0   #counts total special characters

while [ $idx -lt $len ];
do
   x=${s:$idx:1}
   idx=$((idx + 1))
   
   asci=$(printf "%d " "'$x'")    #get the ascii code of the character
   alpha=0
   spcl=0
   num=0
   for((i=65;i<=90;i++))   #check for capital alphabets
   do
      if [ $i -eq $asci ]
      then
         alpha=1
         break
      fi
   done
   
   for((i=97;i<=122;i++))   #check for small alphabets
   do
      if [ $i -eq $asci ]
      then
         alpha=1
         break
      fi
   done
   
   for((i=48;i<=57;i++))   #check for integers (0..9)
   do
      if [ $i -eq $asci ]
      then
         num=1
         break
      fi
   done 
   
   
   if [ $asci -eq 47 -o $asci -eq 60 -o $asci -eq 62 -o $asci -eq 40 -o $asci -eq 41 -o $asci -eq 63 ]   #check for those 6 special characters
   then
	   spcl=1
	   spcls=$((spcls+1))
   fi
   if [ $((num+alpha+spcl)) -eq 0 ]   #if it is neither integer nor alphabets nor special char, it is an invalid password
	   then
	   echo $fail
	   exit
   fi
   
   
done

if [ $spcls -ne 1 ]   #if special chars are not equal to 1, password is invalid
	then
		echo  $fail
	else
		echo $success
fi


