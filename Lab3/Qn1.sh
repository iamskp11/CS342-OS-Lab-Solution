#!/bin/bash
#Author : Saubhik

#This program is pretty straightforward


read -p "Enter length of element:  " n


declare -a arr

for(( i=0; i<n; i++ ))
do
	read -p "Enter  $((i+1))nd number: " num
	arr[$i]=$num
done

read -p "Enter number to search: " S

found=0   #checks if exists or not
idx=-1    #stores the index in it
for (( i=0; i<n; i++ ))
	do
	if [ $S -eq ${arr[$i]} ]
		then 
		found=1
		idx=$i
	fi
done


if [ $found -eq 1 ]
	then 
		echo The number $S was found on index $idx  "(0-based Indexing)"
	else
		echo Number not in array
fi

