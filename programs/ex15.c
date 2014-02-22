#include <stdio.h>

void print_things(int *stuff, char **things, int len) {
    // accepts some pointers
    int i = 0;
    int ble = len; // make sure not size of pointer
    for (i = 0; i < len; i++) {
        printf("%d: %s\n", stuff[i], things[i]);
    }
    printf("---\n");
}

int main(int argc, char *argv[]) {

    // two arrays
    int ages[] = {23, 42, 12, 89, 2};
    char *names[] = {"lee", "on", "li", "ne", "hey"};

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // Use three ways to print things
    // 1. Using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d behind them.\n", names[i], ages[i]); // index ~ address
    }
    printf("---\n");

    // set up pointers to start of array
    int *cur_age = ages;
    char **cur_name = names;
    print_things(cur_age, cur_name, count);
    // notice: sizeof(cur_age) != sizeof(ages) rather size of the pointer

    // 2. Usage of pointers again
    for (i = 0; i < count; i++) {
        printf("%s is %d old.\n", *(cur_name+i), *(cur_age+i));
    }
    printf("---\n");

    // 3. Pointers as arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d you fool!\n", cur_name[i], cur_age[i]);
    }
    printf("---\n");

    // 4. Crazy complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++) {
        printf("%s lived %d years.\n", *cur_name, *cur_age);
    }

    return 0;

}

