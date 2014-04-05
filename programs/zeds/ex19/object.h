// a simple prototype based object system

#ifndef _object_h // "if not defined"
#define _object_h

typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;

// a struct with function pointers and such and such
typedef struct {
    char *description;
    int (*init)(void *self);
    void (*destroy)(void *self);
    void (*describe)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
// a macro
// T##Proto -> concat Proto at the end of T
// E.g. NEW('Leon', 'duToit') -> LeonProto
#define _(N) proto.N
// random syntactic sugar (dubious value)
// obj->proto.ble ~ obj->_(ble)
// sets the proto of the object

#endif
