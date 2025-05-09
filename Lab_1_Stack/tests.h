#ifndef TESTS_H
#define TESTS_H



#define TEST_DYN_ARR_1    ElemArr_t num = 111; dynamic_array_push(&dyn_stack, &num); print_dyn_stack_info(&dyn_stack);\
\
    num = 222; dynamic_array_push(&dyn_stack, &num); print_dyn_stack_info(&dyn_stack);\
\
    num = 333; dynamic_array_push(&dyn_stack, &num); print_dyn_stack_info(&dyn_stack);\
\
    num = 444; dynamic_array_push(&dyn_stack, &num); print_dyn_stack_info(&dyn_stack);\
\
    num = 555; dynamic_array_push(&dyn_stack, &num); print_dyn_stack_info(&dyn_stack);\
\
    dynamic_array_pop(&dyn_stack); print_dyn_stack_info(&dyn_stack);\
\
    dynamic_array_pop(&dyn_stack); print_dyn_stack_info(&dyn_stack);\
\
    dynamic_array_pop(&dyn_stack); print_dyn_stack_info(&dyn_stack);\
\
    dynamic_array_pop(&dyn_stack); print_dyn_stack_info(&dyn_stack);\




#define TEST_LIST_1    ElemArr_t num = 111; list_push(&list, &num); print_list(&list);\
\
    num = 222; list_push(&list, &num); print_list(&list);\
\
    num = 333; list_push(&list, &num); print_list(&list);\
\
    list_pop(&list); print_list(&list);\
\
    list_pop(&list); print_list(&list);\
\
    list_pop(&list); print_list(&list);\


#endif
