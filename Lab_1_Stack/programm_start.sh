gcc main.c dynamic_array/dynamic_array.c singly_linked_list/list.c input/input.c timer.c -o start 2> error1.txt

#-------------TEST_1----------------------------------

./tests_shell/generation_test_1.sh 2> error1.txt

output1=$(./start TEST_1/test1.txt DYN 2>> error1.txt)
echo "$output1"
output2=$(./start TEST_1/test1.txt LIST 2>> error1.txt)
echo "$output2"

time1=$(echo "$output1" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')
time2=$(echo "$output2" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')

if (( $(echo "$time1 < $time2" | bc -l) )); 
then
    echo "Dynamic array better"
else
    echo "Linked list better"
fi

echo
echo

#-------------TEST_2----------------------------------

./tests_shell/generation_test_2.sh 2> error1.txt

output1=$(./start TEST_2/test2.txt DYN 2>> error1.txt)
echo "$output1"
output2=$(./start TEST_2/test2.txt LIST 2>> error1.txt)
echo "$output2"

time1=$(echo "$output1" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')
time2=$(echo "$output2" | grep -oE '[0-9]+(\.[0-9]+)? millisecond' | grep -oE '[0-9]+(\.[0-9]+)?')

if (( $(echo "$time1 < $time2" | bc -l) )); 
then
    echo "Dynamic array better"
else
    echo "Linked list better"
fi

echo
echo

#-------------TEST_3----------------------------------

cd TEST_3
./generation_test_3.sh 2> error1.txt
cd ..

