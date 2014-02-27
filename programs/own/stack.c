#include <stdio.h>

#define MAX_ITEMS 100

struct Stack {
    int top_item_position;
    int next_item_position;
    int stack_items[MAX_ITEMS];
};

void initialise_stack(struct Stack *stack) {
    stack->top_item_position = 0;
    stack->next_item_position = 0;
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {
        stack->stack_items[i] = 0;
    }
}

void increment_stack_counters(struct Stack *stack) {
    if (stack->next_item_position == 0) {
        stack->top_item_position = 0;
    } else {
        int new_top_position = stack->top_item_position + 1;
        stack->top_item_position = new_top_position;
    }
    int new_position = stack->next_item_position + 1;
    stack->next_item_position = new_position;
}

void decrement_stack_counters(struct Stack *stack) {
    if (stack->next_item_position == 0) {
        return;
    } else {
        int new_top_position = stack->top_item_position - 1;
        stack->top_item_position = new_top_position;
        int new_position = stack->next_item_position -1;
        stack->next_item_position = new_position;
    }
}

void push(struct Stack *stack, int item) {
    int current_pos = stack->next_item_position;
    printf("inserting %d into position %d\n", item, current_pos);
    stack->stack_items[current_pos] = item;
    increment_stack_counters(stack);
}

void pop(struct Stack *stack) {
    printf("popped: %d\n", stack->stack_items[stack->top_item_position]);
    decrement_stack_counters(stack);
}

void peek(struct Stack *stack) {
    int top_item_position = stack->top_item_position;
    int item = stack->stack_items[top_item_position];
    printf("top item %d in array position %d \n", item, top_item_position);
}

int main(int argc, char *argv[]) {

    struct Stack stack;
    initialise_stack(&stack);

    push(&stack, 10);
    peek(&stack);

    push(&stack, 14);
    peek(&stack);

    push(&stack, 666);
    peek(&stack);

    pop(&stack);

    push(&stack, 777);
    peek(&stack);

    return 0;
}
