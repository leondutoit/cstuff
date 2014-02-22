#include <stdio.h>

int main(int argc, char *argv[]) {

    int i = argc - 1;
    while (i > 0) {
        printf("Arg %d: %s\n", i, argv[i]);
        i--;
    }

    char *states[] = {"ble"}; // only has space for one element
    int j = 0;
    while (j < argc) {
        states[j] = argv[j];
        j++;
    }

    int num_states = sizeof(states)/sizeof(char*);
    i = num_states;
    while (i >= 0) {
        printf("State %d: %s\n", i, states[i]);
        i--;
    }

    states[2] = "le";
    printf("%s\n", states[2]);

    return 0;
}
