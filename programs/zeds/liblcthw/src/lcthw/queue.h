
#ifndef lcthw_queue_h
#define lcthw_queue_h

#include <lcthw/list.h>

typedef struct Queue {
    List *elem;
    int n;
} Queue;

Queue *Queue_create() {
    return calloc(1, sizeof(Queue));
}

void Queue_send(Queue *queue, void *value) {
    if (queue->n > 0) {
        List_push(queue->elem, value);
    } else {
        queue->elem = List_create();
        List_push(queue->elem, value);
        queue->n = 1;
    }
}

void *Queue_recv(Queue *queue) {
    return List_shift(queue->elem);
}

void *Queue_peek(Queue *queue) {
    return queue->elem->first->value;
}

int Queue_count(Queue *queue) {
    return queue->elem->count;
}

void Queue_destroy(Queue *queue) {
    List_clear_destroy(queue->elem);
    free(queue);
}

#endif
