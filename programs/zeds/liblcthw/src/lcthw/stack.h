
#ifndef lcthw_stack_h
#define lcthw_stack_h

#include <lcthw/list.h>

typedef struct Stack {
    List *elem;
    int n;
} Stack;

Stack *Stack_create() {
    return calloc(1, sizeof(Stack));
}

void Stack_push(Stack *stack, void *value) {
    if (stack->n > 0) {
        List_push(stack->elem, value);
    } else {
        stack->elem = List_create();
        List_push(stack->elem, value);
        stack->n = 1;
    }
}

void *Stack_peek(Stack *stack) {
    return stack->elem->last->value;
}

void *Stack_pop(Stack *stack) {
    return List_pop(stack->elem);
}

int Stack_count(Stack *stack) {
    return stack->elem->count;
}

//#define STACK_FOREACH(stack, first, next, current)\
  //  LIST_FOREACH(stack->elem, stack->elem->first, stack->elem->first->next, current)

void Stack_destroy(Stack *stack) {
    List_clear_destroy(stack->elem);
    free(stack->n);
    free(stack);
}

#endif
