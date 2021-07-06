#!/bin/sh
#Author : Saubhik


# ./Qn3.sh filename number_of_lines

#function to delete or keep file by checking number of lines it has
check()
{
filename=$1
threshold=$2
lines=0

while read line    # iterate over all lines
	do
		lines=`expr $lines + 1`    #increment line by 1
	done< $filename


if [ $lines -lt $threshold ]    # compare number of lines with minimum value
	then
		rm -f $filename
		echo File removed
	else 
		echo Has more lines than required
fi
}

# function to check if filename is correct
fn()      
{
 filename=$1
 if [ -f $filename ]       #check if file is valid
	 then
		 check $filename $2
	 else 
	 	echo No such file exists
 fi

}


#check for correct number of arguments
args=2
if [ $# -ne 2 ]
then
echo "Enter only two arguments"
else 
fn $1 $2
fi

