#include <stdio.h>

int main(int argc, char *argv[]) {

    int i = 0;
    char **pargv = argv; // process argv with pointers

    if (argc == 2) {
        printf("You only have one arg you suck\n");
    } else if (argc > 2 && argc < 8) {
        printf("Here are your args:\n");
        for (i = 0; i < argc; i++) {
            printf("%s \n", pargv[i]);
            printf("The current address of the pointer: %p\n", &argv[i]);
            if (i > 4) {
                break;
            }
        }
    } else {
        printf("You have way too many args\n");
    }

    return 0;
}