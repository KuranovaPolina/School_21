#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0

function testing()
{
    t=$1
    ./s21_cat $t > s21_cat.txt
    cat $t > cat.txt
    diff cat.txt s21_cat.txt > res.txt
    (( COUNTER++ ))
    if [ -f res.txt ]; then
        if [ -s res.txt ]; then
             (( FAIL++ ))
            echo "fail cat $t"
        else
            (( SUCCESS++ ))
            echo "success cat $t"
        fi
    fi
    rm s21_cat.txt cat.txt res.txt
}

for filename in "test1_cat.txt" "test2_cat.txt" "test3_cat.txt" "test4_cat.txt"
do
    testing $filename

    for var1 in b e E n s t T v
    do
        testing "-$var1 $filename"
    done

    for var1 in b e E n s t T v
    do
        for var2 in b e E n s t T v
        do
            testing "-$var1$var2 $filename"
        done
    done

    testing "-benst $filename"
    testing "-bEnsT $filename"
    testing "-beEnstTv $filename"

done

testing "-benst test4_cat.txt test4_cat.txt"
testing "test1_cat.txt test2_cat.txt"

echo ""
echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
