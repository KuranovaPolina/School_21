#!/bin/bash

. ./library.sh

start=$(date +%s.%N);

if [ $# -eq 1 ]
then
    if [[ $1 =~ /$ ]]
    then
        if [[ -d $1 ]]
        then
            dirpath=$(makeNormalFileName $1);
            collectData ${dirpath};
            end=$(date +%s.%N);
            echo "Script execution time (in seconds) = $( echo "$end $start" | awk '{printf "%.1lf", $1-$2}' )";
    else
            echo "Directory not exists or it is not a directory.";
        fi;
    else
        echo "Incorrect directory name.";
    fi;
else
    echo "Incorrect argument count. Add only directory name.";
fi;
