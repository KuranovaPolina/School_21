#!/bin/bash

. ./library.sh

config_file="config.config";

column1_background=$(normalizeColorValue $(cat ${config_file} | grep "column1_background" | awk 'BEGIN{FS="="} {print $2}'));
column1_font_color=$(normalizeColorValue $(cat ${config_file} | grep "column1_font_color" | awk 'BEGIN{FS="="} {print $2}'));
column2_background=$(normalizeColorValue $(cat ${config_file} | grep "column2_background" | awk 'BEGIN{FS="="} {print $2}'));
column2_font_color=$(normalizeColorValue $(cat ${config_file} | grep "column2_font_color" | awk 'BEGIN{FS="="} {print $2}'));

getColors ${column1_background} ${column1_font_color} ${column2_background} ${column2_font_color};

if [[ $(parametrsCheck) -eq 1 ]]
then   
    collectData;
    showData;
    echo "";
    showConfigs ${column1_background} ${column1_font_color} ${column2_background} ${column2_font_color};
else 
    echo "Background or font colors are the same. Please, restart the script.";
fi;

