#!/bin/bash

. ./library.sh

collectData;
showData;

echo "Save in file? [Y/N]";

read choice;

if [[ $choice =~ ^[yY]{1}$ ]]
then
    writeData;
fi;
