#!/bin/bash

col1_bg_code="'\033[39m'";
col1_fc_code="'\033[49m'";
col2_bg_code="'\033[39m'";
col2_fc_code="'\033[49m'";
color_end_code="\033[0m";

function collectData {
    hostname=$HOSTNAME;
    timezone="$(cat /etc/timezone) $(date +"%Z %z")";
    user=$USER;
    os=$(cat /etc/issue | awk '{print $1, $2, $3}' | tr -d '\r\n');
    date=$(date +"%d %b %Y %H:%M:%S");
    uptime=$(uptime -p);
    uptime_sec=$(awk '{print $1}' /proc/uptime);
    ip=$(hostname -I | awk '{print $1}');
    mask=$(ifconfig | grep $ip | awk '{print $4}');
    gateway=$(ip route | grep default | awk '(NR == 1)' | awk '{printf $3}');
    ram_total=$(free | grep Mem: | awk '{printf("%.3f GB", $2/1024/1024)}');
    ram_used=$(free | grep Mem: | awk '{printf("%.3f GB", $3/1024/1024)}');
    ram_free=$(free | grep Mem: | awk '{printf("%.3f GB", $4/1024/1024)}');
    space_root=$(df | grep /$  | awk '{printf("%.2f MB", $2/1024)}');
    space_root_used=$(df | grep /$  | awk '{printf("%.2f MB", $3/1024)}');
    space_root_free=$(df | grep /$  | awk '{printf("%.2f MB", $4/1024)}');
}

function showData {
    echo -e "${col1_bg_code}${col1_fc_code}HOSTNAME${color_end_code} = ${col2_bg_code}${col2_fc_code}$hostname${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}TIMEZONE${color_end_code} = ${col2_bg_code}${col2_fc_code}$timezone${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}USER${color_end_code} = ${col2_bg_code}${col2_fc_code}$user${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}OS${color_end_code} = ${col2_bg_code}${col2_fc_code}$os${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}DATE${color_end_code} = ${col2_bg_code}${col2_fc_code}$date${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}UPTIME${color_end_code} = ${col2_bg_code}${col2_fc_code}$uptime${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}UPTIME_SEC${color_end_code} = ${col2_bg_code}${col2_fc_code}$uptime_sec${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}IP${color_end_code} = ${col2_bg_code}${col2_fc_code}$ip${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}MASK${color_end_code} = ${col2_bg_code}${col2_fc_code}$mask${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}GATEWAY${color_end_code} = ${col2_bg_code}${col2_fc_code}$gateway${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}RAM_TOTAL${color_end_code} = ${col2_bg_code}${col2_fc_code}$ram_total${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}RAM_USED${color_end_code} = ${col2_bg_code}${col2_fc_code}$ram_used${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}RAM_FREE${color_end_code} = ${col2_bg_code}${col2_fc_code}$ram_free${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}SPACE_ROOT${color_end_code} = ${col2_bg_code}${col2_fc_code}$space_root${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}SPACE_ROOT_USED${color_end_code} = ${col2_bg_code}${col2_fc_code}$space_root_used${color_end_code}";
    echo -e "${col1_bg_code}${col1_fc_code}SPACE_ROOT_FREE${color_end_code} = ${col2_bg_code}${col2_fc_code}$space_root_free${color_end_code}";
}

function getColors {
    col1_bg_code="$( getBackgroundColor $1)";
    col1_fc_code="$( getFontColor $2)";
    col2_bg_code="$( getBackgroundColor $3)";
    col2_fc_code="$( getFontColor $4)";
}

function getFontColor {
    case $1 in
        1) echo '\033[97m';;
        2) echo '\033[31m';;
        3) echo '\033[32m';;
        4) echo '\033[34m';;
        5) echo '\033[35m';;
        6) echo '\033[30m';;
    esac;
}

function getBackgroundColor {
    case $1 in
        1) echo '\033[107m';;
        2) echo '\033[41m';;
        3) echo '\033[42m';;
        4) echo '\033[44m';;
        5) echo '\033[45m';;
        6) echo '\033[40m';;
    esac;
}

function parametrsCheck {
    if [[ $(parametrCheck $1) -eq 1 ]] && [[ $(parametrCheck $2) -eq 1 ]] && [[ $(parametrCheck $3) -eq 1 ]] && [[ $(parametrCheck $4) -eq 1 ]] 
    then
        echo 1;
    else
        echo 0;
    fi;
}

function parametrCheck {
    if [[ $1 -ge 1 ]] && [[ $1 -le 6 ]] 
    then
        echo 1;
    else
        echo 0;
    fi;
}
