# cd Generation_tests/
# ./generation_tests.sh 1 10000 50
# cd ..

gcc main.c timer.c Sorts/quadratic_sorts/bubble_sort.c Sorts/quadratic_sorts/insertion_sort.c Sorts/quadratic_sorts/selection_sort.c Sorts/quadratic_sorts/shell_sort.c Check_tests/tester.c Sorts/Merge_sort/merge_sort.c Sorts/Quick_sort/quick_sort.c -o programm_start
echo "Я поехал"
./programm_start
