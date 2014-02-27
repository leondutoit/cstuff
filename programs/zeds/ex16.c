#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// define the new type
struct Person { // a compound type
    char *name;
    int age;
    int height;
    int weight;
};

// Just another one
struct Anotherperson {
    char *name;
    int age;
};

// pass struct to method without a pointer
void print_another_person(struct Anotherperson ap) {
    printf("%s\n", ap.name);
    printf("%d\n", ap.age);
}

// to use without keyword
typedef struct {
    int blergh;
} Bbb;

// function to create persons
struct Person *Person_create(char *name, int age, int height, int weight) {
    struct Person *who = malloc(sizeof(struct Person)); // constructed on the heap
    assert(who != NULL); // make sure piece of memory is valid

    who->name = strdup(name); // strdup copies the name, belongs in new memory now
    who->age = age; // initialize values
    who->height = height;
    who->weight = weight;

    return who;
}

// destory persons and free memory
void Person_destroy(struct Person *who) {
    assert(who != NULL); // make sure not getting bad input

    free(who->name); // return memory you got from strdup
    free(who); // return memory you got from malloc (not doing this is a memory leak)
}

// look at persons
void Person_print(struct Person *who) {
    printf("Name: %s\n", who->name);
    printf("Age: %d\n", who->age);
    printf("Height: %d\n", who->height);
    printf("Weight: %d\n", who->weight);
}

// do stuff
int main(int argc, char *argv[]) {

    struct Person *leon = Person_create("leon du toit", 29, 179, 73);
    struct Person *line = Person_create("line simenstad", 28, 170, 65);

    printf("Leon is at memory location: %p\n", leon);
    Person_print(leon);

    printf("Line is at memory location: %p\n", line);
    Person_print(line);

    // Change them!
    leon->age += 10; // can reference sub-parts
    line->age += 4;

    struct Anotherperson pooz; // created on the stack
    pooz.name = "POOZ";
    pooz.age = 90;
    printf("Pooz lives at: %p\n", &pooz);
    print_another_person(pooz); // passing a struct as a normal param


    Person_print(leon);
    Person_print(line);

    // Clean up
    Person_destroy(leon);
    Person_destroy(line);

    return 0;
}
