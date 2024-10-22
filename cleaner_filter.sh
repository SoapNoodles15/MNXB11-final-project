#!/bin/bash

#This function tells the user how to use the script
#in case of an error
HowTo(){
	echo "=========="
	echo -e "To use this script you need to write"
	echo -e "   $0 '<path-to-datafile>'"
    echo -e "It must be a path to the datafile"
	echo -e "Example:"
    echo -e "   $0 '../data/smhi_datafile.csv'"
	echo "=========="
}


PROJECT_SMHIINPUT=$1

#Checking if the input variable is defined
if [[ "x$PROJECT_SMHIINPUT" == 'x' ]]; then
   echo "Missing input file parameter, exiting" 1>&2
   HowTo
   exit 1
fi

#Extracting the filename to be used in the output files
PROJECT_DATAFILE=$(basename $PROJECT_SMHIINPUT)

#Pre-defining names for output files in variables so that they can be
#used everywhere in the code
PROJECT_ORIGINALFILENAME="original_${PROJECT_DATAFILE}"
PROJECT_BAREDATAFILENAME="baredata_${PROJECT_DATAFILE}"


#If $PROJECT_SMHIINPUT not empty
if [[ "x$PROJECT_SMHIINPUT" != "x" ]]; then
   #Checking if the file is a directory
   if [[ -d $PROJECT_SMHIINPUT ]]; then
      echo -e "This script requires a data file and not a directory, exiting..." 1>&2
      exit 1
   fi
   #Copying the file in the current directory as
   #    original_$PROJECT_DATAFILE
   cp -a $PROJECT_SMHIINPUT $PROJECT_ORIGINALFILENAME
   #Capture copy errors
   PROJECT_COPY_OUTCOME=$?
fi 

#Checking that the input file has been copied without issues
if [[ $PROJECT_COPY_OUTCOME != 0 ]]; then
   echo "Error downloading or copying file, check filename or command syntax. Exiting...." 1>&2
   HowTo
   exit 1
fi

#Detirmining where the wanted data starts
STARTLINE=$(grep -n 'Datum' $PROJECT_ORIGINALFILENAME | cut -d':' -f 1)

STARTLINE=$(( $STARTLINE + 1 ))

#Removing unnecessary lines at the start of the datafile, fixing format for the lines with comments, converting semicolons into commas
tail -n +$STARTLINE $PROJECT_ORIGINALFILENAME | cut -d';' -f 1,2,3,4,5 | sed 's/;/,/g' > $PROJECT_BAREDATAFILENAME

FILTER_FILTEREDFILENAME="filtered_${PROJECT_DATAFILE}"

FILTER_FILTERFILENAME_ONLY26APRIL="26April_$FILTER_FILTEREDFILENAME"
grep '\-04\-26,1[2-3]:00:00' $PROJECT_BAREDATAFILENAME > $FILTER_FILTERFILENAME_ONLY26APRIL

FILTER_FILTERFILENAME_COLDWARM="ColdestWarmest_$FILTER_FILTEREDFILENAME"
awk -F',' '{

    #Extracting year and temperature
    year = substr($1, 1, 4);
    temp = $3;

    #Storing the warmest and coldest temp for each year using 
    #associative arrays/dictionaries
    if(year in coldest){

        if(temp < coldest[year]){ coldest[year] = temp; coldest_line[year] = $0}
        if(temp > warmest[year]){ warmest[year] = temp; warmest_line[year] = $0}
    }

    else{
        coldest[year] = temp
        warmest[year] = temp
        coldest_line[year] = $0
        warmest_line[year] = $0
    }

 }
 END {
    #Writing all the warmest and coldest temp entries to a file
    for (year in coldest){
        print coldest_line[year];
        print warmest_line[year];
    }
 }' $PROJECT_BAREDATAFILENAME > $FILTER_FILTERFILENAME_COLDWARM