#!/bin/bash

gcc Create_ONE_Test/create_test.c -o Create_ONE_Test/create_test
gcc Sort_ONE_Test/sort_test.c -o Sort_ONE_Test/sort_test


read -p "Введите начальное число (from): " from
read -p "Введите конечное число (to): " to
read -p "Введите шаг (step): " step


current=$from
while [ "$current" -le "$to" ]; 
do
    counter=1
    while [ "$counter" -le 5 ]; 
    do
        file_in="TESTS/"$current"_"$counter".in"
        : > "$file_in"
        file_out="TESTS/"$current"_"$counter".out"
        : > "$file_out"

        Create_ONE_Test/create_test "$current" $RANDOM >> "$file_in"
        Sort_ONE_Test/sort_test "$file_in" "$current" >> "$file_out"

        counter=$((counter + 1))
        # sleep 1
    done

    # echo -n "$current "
    current=$((current + step))
done