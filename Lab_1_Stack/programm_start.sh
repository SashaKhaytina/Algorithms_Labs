gcc main.c dynamic_array/dynamic_array.c singly_linked_list/list.c input/input.c -o start

./tests_shell/generation_test_1.sh

./start TEST_1/test1.txt DYN
./start TEST_1/test1.txt LIST

echo Dynamic array better


./tests_shell/generation_test_2.sh

./start TEST_2/test2.txt DYN
./start TEST_2/test2.txt LIST

echo Dynamic array better again


cd TEST_3
./generation_test_3.sh
echo Dynamic array better again
cd ..