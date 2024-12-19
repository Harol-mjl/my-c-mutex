#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "my_lib.h"
#include <pthread.h>

#define N 1000000
#define N_THREADS 10
#define ERROR -1
#define SUCCESS 1

void add_n_elements_to_stack(struct my_stack *stack, int n_elements, int size){
    for(int i = 0; i < n_elements; i++){
        int *data = (int *)malloc(size);
        if(!data){
            my_stack_purge(stack);
        }
        *data = 0;
        my_stack_push(stack, data);
    }
}

struct my_stack *create_stack_if_not_exist(int size){
    struct my_stack *stack_aux = my_stack_init(size);
    if(!stack_aux){
        return NULL;
    }
    add_n_elements_to_stack(stack_aux, N_THREADS, size);
    return stack_aux;
}

void fill_stack_to_x_elements(struct my_stack *stack, int n_elements, int size){
    int len_stack = my_stack_len(stack);

    if(len_stack < n_elements){
        printf("rellenando pila hasta 10 elementos");
        int elements_to_add = n_elements - len_stack;
        add_n_elements_to_stack(stack, elements_to_add, size);
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
        printf("creando pila que no existe");
        stack = create_stack_if_not_exist(sizeof(int));
        if(!stack){
            return ERROR;
        }
        fill_stack_to_x_elements(stack, N_THREADS, sizeof(int));
    }
    fill_stack_to_x_elements(stack, N_THREADS, sizeof(int));
    my_stack_write(stack, argv[1]);
    return 0;
}
