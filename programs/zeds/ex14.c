#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
// only needed if used before defined
//int can_print_it(char ch);
//void print_letters(char arg[]);

//int can_print_it(char ch) {
  //  return isalpha(ch) || isblank(ch); // from ctype.h
//}

void print_letters(char arg[], int str_len) {
    int i = 0;
    for (i = 0; i < str_len; i++) {
        char ch = arg[i];
        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d \n", ch, ch);
        } else {
            break;
        }
    }
    printf("\n");
}

void print_arguments(int argc, char *argv[]) {
    int i = 0;
    for (i = 0; i < argc; i++) {
        print_letters(argv[i], strlen(argv[i]));
    }
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}
