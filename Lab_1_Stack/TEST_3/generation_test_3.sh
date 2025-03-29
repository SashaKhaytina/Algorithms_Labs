gcc create_test_3.c ../dynamic_array/dynamic_array.c ../singly_linked_list/list.c ../input/input.c ../timer.c -o start_test3

output1=$(./start_test3 test3.txt DYN 2>> ../error1.txt)
echo "$output1"
output2=$(./start_test3 test3.txt LIST 2>> ../error1.txt)
echo "$output2"

time1=$(echo "$output1" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')
time2=$(echo "$output2" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')

if (( $(echo "$time1 < $time2" | bc -l) )); 
then
    echo "Dynamic array better"
else
    echo "Linked list better"
fi