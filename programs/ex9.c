#include <stdio.h>

int main(int argc, char *argv[]) {

    int numbers[4] = {0}; // array with 4 zeros
    char name[4] = {'a', 'a', 'a', '\0'};

    // print them out raw
    printf("numbers: %d %d %d %d\n",
        numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
        name[0], name[1], name[2], name[3]);

    // setup numbers (as strings)
    numbers[0] = 'u';
    numbers[1] = 'q';
    numbers[2] = 'a';
    numbers[3] = 'z';

    // setup name
    //name[0] = 5;
    //name[1] = 6;
    //name[2] = 7;
//    name[3] = '\0'; // terminator - need in C style strings

    // print them out initialised
    printf("numbers: %d %d %d %d\n",
        numbers[0], numbers[1], numbers[2], numbers[3]);

    printf("name each: %d %d %d %d\n",
        name[0], name[1], name[2], name[3]);

    printf("name char array as an int: %c\n", name[0]);

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed"; // idiomatic sting literal syntax

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
        another[0], another[1], another[2], another[3]);

    printf("%ld\n", sizeof(name[0]));

    return 0;
}
