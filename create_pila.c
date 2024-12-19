#include <stdio.h>
#include <pthread.h>
#include "my_lib.h"

#define NODES 4
#define ROJO "\x1b[31m"
#define RESET "\033[0m"

struct my_data {
    int val;
    char name[60];
};

void fill_stack(my_stack *stack){
    for (int i = 0; i < NODES; i++) {
        data = malloc(sizeof(struct my_data)); 
        if (!data) {
            fprintf(stderr, ROJO "Out of memory\n" RESET);
            exit(EXIT_FAILURE);
        }
        data->val = values[i];

        sprintf(data->name, "Element %d", i);
        my_stack_push(stack, data);
        printf("New node in stack: (%d, %s)\n", data->val, data->name);
    }
}

int main(int argc, char *args[]){
    int values[NODES] = {4,5,6,7};
    struct my_stack *stack;
    struct my_data *data;

    stack = my_stack_init(sizeof(struct my_data));
    fill_stack(stack);
    my_stack_write(stack, args[1]);

  return 0;
}
