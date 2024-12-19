#include <stdio.h>
#include "my_lib.h"

#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define NEGRITA "\x1b[1m"
#define RESET "\033[0m"

#define ERROR -1

struct my_data {
    int val;
    char name[60];
};
void print_statistics(int size_stack, int max, int min, int sum, int mean){
    printf("Items:%d,Max:%d, Min:%d, Suma:%d, Average:%d\n",
            size_stack,
            max,
            min,
            sum,
            mean
    );
}
int main(int argc, char *args[]){
    struct my_stack *stack;
    struct my_data *data;
    
    //Verify if the first parameter is null
    if (!args[1]) {
        fprintf(stderr, ROJO "Error, the first parameter can't be '%s'\n" RESET, args[1]);
        return ERROR;
    }

    //Verify if the file exist
    stack = my_stack_read(args[1]);
    if (!stack) {
        return ERROR;
    }
    
    int size_stack;
    int index = 0;
    int sum, max, min, mean;
    
    size_stack = my_stack_len(stack);
    
    printf("Stack length:%d\n", size_stack);

    if((data = my_stack_pop(stack)) == NULL){
        print_statistics(size_stack, max, min, sum, mean);
    }else{
        index += 1;
        max = data->val;
        min = data->val;
        sum = data->val;
        mean = data->val;
        printf("%d\n", data->val);
    }

    while(index < size_stack && ((data = my_stack_pop(stack)) != NULL)){
        printf("%d\n", data->val);
        if(min > data->val){
            min = data->val;
        }
        if(max < data-> val){
            max = data->val;
        }
        index += 1;
        sum += sum;
        mean = sum/size_stack;
    }

    print_statistics(size_stack, max, min, sum, mean);
    return 0;
}


