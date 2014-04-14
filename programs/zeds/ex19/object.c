#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

// define what was declared in header file

void Object_destroy(void *self) {
    Object *obj = self;
    if (obj) {
        if (obj->description) free(obj->description);
        free(obj);
    }
}

void Object_describe(void *self) {
    Object *obj = self;
    printf("%s.\n", obj->description);
}

int Object_init(void *self) {
    return 1;
}

void *Object_move(void *self, Direction direction) {
    assert(sizeof(direction) > 0);
    printf("You can't go that direction.\n");
    return NULL;
}

int Object_attack(void *self, int damage) {
    assert(damage >= 0);
    printf("You can't attack that.\n");
    return 0;
}

// size_t unigned integer of at least 16 bits
void *Object_new(size_t size, Object proto, char *description) {
    assert(sizeof(size) > 16);
    assert(sizeof(proto)> 0);
    assert(description != NULL);

    // default functions if not set
    if (!proto.init) proto.init = Object_init;
    if (!proto.describe) proto.describe = Object_describe;
    if (!proto.destroy) proto.destroy = Object_destroy;
    if (!proto.attack) proto.attack = Object_attack;
    if (!proto.move) proto.move = Object_move;

    // make a struct of one size
    // then point a different pointer at it, to "cast" it
    Object *el = calloc(1, size); // get a pointer to some memory
    assert(el != NULL);
    *el = proto;

    // copy the description
    el->description = strdup(description);

    // initialise
    if (!el->init(el)) {
        // something wrong with init
        el->destroy(el);
        return NULL;
    } else {
        // made an object of any type
        return el;
    }
}

