#!/bin/bash

function collectData {
    hostname=$HOSTNAME;
    timezone="$(cat /etc/timezone) $(date +"%Z %z")";
    user=$USER;
    os=$(cat /etc/issue);
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
    echo "HOSTNAME = $hostname";
    echo "TIMEZONE = $timezone";
    echo "USER = $user";
    echo "OS = $os";
    echo "DATE = $date";
    echo "UPTIME = $uptime";
    echo "UPTIME_SEC = $uptime_sec";
    echo "IP = $ip";
    echo "MASK = $mask";
    echo "GATEWAY = $gateway";
    echo "RAM_TOTAL = $ram_total";
    echo "RAM_USED = $ram_used";
    echo "RAM_FREE = $ram_free";
    echo "SPACE_ROOT = $space_root";
    echo "SPACE_ROOT_USED = $space_root_used";
    echo "SPACE_ROOT_FREE = $space_root_free";
}

function writeData {
    filename=$(date +"%d_%m_%y_%H_%M_%S")".status";
    touch "$filename";

    echo "HOSTNAME = $hostname" >> $filename;
    echo "TIMEZONE = $timezone" >> $filename;
    echo "USER = $user" >> $filename;
    echo "OS = $os" >> $filename;
    echo "DATE = $date" >> $filename;
    echo "UPTIME = $uptime" >> $filename;
    echo "UPTIME_SEC = $uptime_sec" >> $filename;
    echo "IP = $ip" >> $filename;
    echo "MASK = $mask" >> $filename;
    echo "GATEWAY = $gateway" >> $filename;
    echo "RAM_TOTAL = $ram_total" >> $filename;
    echo "RAM_USED = $ram_used" >> $filename;
    echo "RAM_FREE = $ram_free" >> $filename;
    echo "SPACE_ROOT = $space_root" >> $filename;
    echo "SPACE_ROOT_USED = $space_root_used" >> $filename;
    echo "SPACE_ROOT_FREE = $space_root_free" >> $filename;
}
