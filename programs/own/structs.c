#include <stdio.h>

// either defined at the top of a .c file
// or in header file

// option 1
struct Leon {
    int x;
    int array[100];
};

// option 2
typedef struct {
    int x;
    int array[100];
} Line;

void try_to_change_me(struct Leon leon) {
    leon.x = 30;
    leon.array[3] = 0;
}

void change_me_for_real(struct Leon *leon) {
    leon->x = 30;
    leon->array[3] = 0;
}

int main(int argc, char *argv[]) {

    struct Leon leon; // automatic allocation on the stack
    leon.x = 29;
    leon.array[3] = 100;
    leon.array[4] = 9;
    printf("leon.array[3]: %d\n", leon.array[3]);
    printf("leon.array[4]: %d\n", leon.array[4]);

    Line line; // don't have to declare struct here
    line.x = 17;
    line.array[3] = 200;

    printf("leon.x is: %d\n", leon.x);
    printf("line.x is: %d\n", line.x);
    printf("size leon: %d\n", sizeof(leon));
    printf("size line: %d\n", sizeof(line));

    try_to_change_me(leon);
    printf("after being changed leon.x is still: %d\n", leon.x);

    change_me_for_real(&leon);
    printf("having been changed for real now leon.x is: %d\n", leon.x);

    change_me_for_real_2(leon);
    printf("is leon.x different???: %d\n", leon.x);

    return 0;
}