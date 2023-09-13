#!/bin/bash

if ! [ $# -eq 1 ]
then
        echo "incorrect argument count"
else
        if [[ $1 =~ ^-?[0-9]+([.][0-9]+)?$ ]]
        then
                echo "argument is a number"
        else
                echo $1
        fi
fi
