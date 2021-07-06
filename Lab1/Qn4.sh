#!/bin/sh
#Author : Saubhik


# ./Qn4.sh directory_name pattern new_name

change_name()     #function to change name to given new name 
{
   directory=$1      #get the arguments into appropriate variables
   filename=$2
   pat=$3
   new_name=$4
   pat_len=`expr $(echo $3 | wc -m) - 1`    # find the length of the pattern string
   if echo "$2" | grep -q "$3"              # check if pattern exist in the file name
   	then
   		mv $directory/$filename $directory/$new_name"_"$count".txt"    # change the name
   	        count=`expr $count + 1`
   fi
   
}

fn()             # function to extract all files having extenstion .txt
{
  directory=$1
  pat=$2
  name=$3
  for f in $directory/*
  do
	  filename=`expr $(basename $f)`   # get the filename
	  extension="${filename##*.}"      #get the extenxionS
  if test "$extension" = "txt" 
	  then
	   	change_name $directory $filename $pat $name
	  fi
  done
}

args=3
count=1

# check for correct arguments passing
if [ $# -ne $args ]
	then
		echo Enter 3 arguments only
	else 
		fn $1 $2 $3
fi

#print how many files you changed
count=`expr $count - 1`
echo  $count files name changed


