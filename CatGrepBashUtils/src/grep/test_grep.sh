#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

function testing()
{
    t=$1
    grep $t > grep.txt
    ./s21_grep $t > s21_grep.txt
    diff grep.txt s21_grep.txt > res.txt
    (( COUNTER++ ))
    if [ -f res.txt ]; then
        if [ -s res.txt ]; then
             (( FAIL++ ))
            echo "fail grep $t"
        else
            (( SUCCESS++ ))
            echo "success grep $t"
        fi
    fi
    rm s21_grep.txt grep.txt res.txt
}

for filename in "test1_grep.txt" "test2_grep.txt" "test3_grep.txt"
do
    testing "-e include $filename"
    testing "-e ^#include $filename"
    testing "-e define $filename"
    testing "-e ^[a-zA-Z] $filename"
    testing "-e ^[0-9] $filename"

    for var1 in i n v c l n h s
    do
        testing "-$var1 include $filename"
        testing "-$var1 ^#include $filename"
        testing "-$var1 define $filename"
        testing "-$var1 ^[a-zA-Z] $filename"
        testing "-$var1 ^[0-9] $filename"
    done
done

for var1 in i n v c l n h s
    do
        testing "-e include -$var1 test1_grep.txt"
    done

for var1 in i n v c l n h
    do
        testing "-$var1 include test1_grep.txt test2_grep.txt"
        testing "-$var1 ^#include test1_grep.txt test2_grep.txt"
        testing "-$var1 define test1_grep.txt test2_grep.txt"
        testing "-$var1 ^[a-zA-Z] test1_grep.txt test2_grep.txt"
        testing "-$var1 ^[0-9] test1_grep.txt test2_grep.txt"
    done

for var1 in i n v c l n h
    do
        for var2 in i n v c l n h
        do
            testing "-$var1$var2 include test1_grep.txt test2_grep.txt"
            testing "-$var1$var2 ^#include test1_grep.txt test2_grep.txt"
        done
    done

testing "-lcn include test1_grep.txt test2_grep.txt"
testing "-lch include test1_grep.txt test2_grep.txt"
testing "-lnh include test1_grep.txt test2_grep.txt"
testing "-cnh include test1_grep.txt test2_grep.txt"
testing "-lcnh include test1_grep.txt test2_grep.txt"

testing "-s ^[0-9] test_grep"
testing "-s ^[0-9] test_grep test1_grep.txt"

testing "-e include -e define $filename"

echo ""
echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
