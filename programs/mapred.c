#include <stdio.h>

// a silly in-place map reduce on integer array-like structs ~ lists
// prints the sum of squares from an integer array
// for shits and giggles

struct List {
    int length;
    int elements[];
};

typedef int (*func_one)(int a);
typedef int (*func_two)(int a, int b);

void init_list(struct List *list, int *numbers, int count) {
    list->length = count;
    int i = 0;
    for (i = 0; i < count; i++) {
        list->elements[i] = numbers[i];
    }
}

int sum(int a, int b) {
    return a + b;
}

int square(int a) {
    return a * a;
}

struct List *map(func_one func, struct List *list) {
    int i = 0;
    int length = list->length;
    for (i = 0; i < length; i++) {
        list->elements[i] = square(list->elements[i]);
    }
    return list;
}

int reduce(func_two func, struct List *list) {
    int cumul = 0;
    int i = 0;
    int length = list->length;
    for (i = 0; i < length - 1; i++) {
        cumul += sum(list->elements[i], list->elements[i + 1]);
    }
    printf("%d\n", cumul);
    return cumul;
}

int main(int argc, char *argv[]) {

    int some_nums[] = {3,4,5,1};
    int count = sizeof(some_nums) / sizeof(int);
    struct List list;
    init_list(&list, some_nums, count);

    reduce(sum, map(square, &list));

    return 0;
}
