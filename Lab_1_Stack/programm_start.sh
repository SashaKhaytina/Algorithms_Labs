./tests_shell/generation_test_1.sh

gcc main.c dynamic_array/dynamic_array.c singly_linked_list/list.c input/input.c -o start

./start TEST_1/test1.txt LIST
./start TEST_1/test1.txt DYN

echo Dynamic array better