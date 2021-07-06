
# get the filename and k from CLA
checkfile=$1
k=$2

# Read all words of given file and store their frequency in freq array
declare -A freq
while read -ra line; 
do
    for word in "${line[@]}";
    do
        let freq[$word]+=1
    done;
done < $checkfile

# echo ${freq[*]}    #(Print all values )

# get all words that have frequency greater than k and store them in words array
declare -A words
for key in "${!freq[@]}"; 
do 
if [ ${freq[$key]} -gt $k ] 
then
words[${#words[@]}]=$key
fi
done


# Print all such words
echo "Words who frequency is greater than $k are "
echo ${words[*]}


#function to replace all words with MASKED 
edit()
{
    file=$1
    replace="MASKED"
    len=${#words[@]}
    for (( i=0; i<${len}; i++ ));
	do
	  search=${words[$i]}
	  sed -i "s/\b$search\b/$replace/g" $file
	done
		
}


for FILE in *; 
	do 
		ext="${FILE##*.}"
	if [[ "$ext" == "txt" && "$FILE" != $checkfile ]];
		then
			edit $FILE 
		fi
	done


# declare arrays to store words 
declare -A FreqMask                    # Stores words that have freq >= k/2
declare -A MaskCount                   # stores filename and the frequncy of MASKED in it as associative arrayS
declare -A FreqMask1                   # stores filename in descending order of MASKED in it


answer=$((($k / 2) + ($k% 2 > 0)))     # taking the ceil(k/2)

#function checks number of MASKED in a file
check()
{
	file=$1
	replace="MASKED"
    count=0;
    for i in `cat $file`;
        do if [ $i == "$replace" ];
    then ((count++)) 
    fi; 
    done;
    if [ $count -gt $answer ]
    then
    FreqMask[${#FreqMask[@]}]=$file
    MaskCount[$file]=$count
    fi
    
}


# recursive function to sort the associative array in descending order of number of MASKED 
sortIt()
{

length=${#FreqMask1[@]}
length2=${#FreqMask[@]}
if [ $length -eq $length2 ]
then 
	return 
fi
mini=1000000
fname="xyx.txt"
for key in "${!MaskCount[@]}"; 
	do 
	if [ ${MaskCount[$key]} -lt $mini ] 
		then
			mini=${MaskCount[$key]}
			fname=$key
	fi
done

FreqMask1[${#FreqMask1[@]}]=$fname
MaskCount[$fname]=2000000

#call the function again
sortIt
}

#Iterate over all txt files in directory except given file
for FILE in *; 
do 
ext="${FILE##*.}"
if [[ "$ext" == "txt" && "$FILE" != $checkfile ]];
then
	check $FILE 
fi

done



length=${#FreqMask[@]}

if [ $length -lt $k ];
	then
	echo "Number of files which have MASKED > $answer is $length (less than $k)"
	echo "Such Files are : "
	echo ${FreqMask[*]}
else 
	sortIt
	echo "Number of files which have MASKED > $answer is $length (atleast $k)"
	echo "Files are (in descending order of frequency of MASKED) : "
	echo ${FreqMask1[@]:0:($k)}
fi





