#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "my_lib.h"
#include <pthread.h>

#define N 1000000
#define N_THREADS 10

void add_n_elements_to_stack(int n_elements){
    for(int i = 0; i < n_elements; i++){
        int *data = (int *)malloc(size);
        if(!data){
            my_stack_purge(stack);
            return NULL;
        }
        *data = 0;
        my_stack_push(stack, data);
    }
}

struct my_stack *create_stack_if_not_exist(int size){
    struct stack_aux = my_stack_init(size);
    if(!stack){
        return NULL;
    }
    add_n_element_to_stack(N_THREADS);
    return stack;
}

void fill_stack_to_x_elements(struct my_stack *stack, int n_elements){
    int len_stack = my_stack_len(stack);

    if(len_stack < n_elements){
        int elements_to_add = n_elements - len_stack;
        add_n_elements_to_stack(elements_to_add);
    }
}


int main(int argc, char* argv[]){
    struct my_stack *stack;
    pthread_t treads[N_THREADS]; 

    if(!argv[1]){
        return ERROR;
    }

    stack = my_stack_read(argv[1]);
    if(!stack){
        stack = create_stack_if_not_exist(sizeof(int));
        if(!stack){
            return ERROR;
        }
        fill_stack_to_x_elements(stack);
    }
    my_stack_write(stack, argv[1]);
    return 0;
}
