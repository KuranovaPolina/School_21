#!/bin/bash

. ./library.sh

if [[ $# -eq 4 ]]
then
    if [[ $(parametrsCheck $1 $2 $3 $4) -eq 1 ]]
    then
        if [[ $1 -ne $2 ]] && [[ $3 -ne $4 ]]  
        then
            getColors $1 $2 $3 $4;
            collectData;
            showData;
        else 
            echo "Background or font colors are the same. Please, restart the script.";
        fi;
    else
        echo "Incorrect arguments. Please, restart the script.";
    fi;
else
    echo "Incorrect argument count. Please, restart the script.";
fi;
