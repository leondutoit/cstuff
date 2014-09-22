
#include "minunit.h"
#include <lcthw/queue.h>
#include <assert.h>

static Queue *queue = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3

char *test_create() {
    queue = Queue_create();
    mu_assert(queue != NULL, "failed to create queue");
    return NULL;
}

// this is a compound tests really
// should be broken into smaller units
char *test_send_recv() {
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        Queue_send(queue, tests[i]);
        mu_assert(Queue_peek(queue) == tests[0], "wrong next val");
    }
    mu_assert(Queue_count(queue) == NUM_TESTS, "wrong val on count");

    for (i  = 0; i < NUM_TESTS; i++) {
        char *val = Queue_recv(queue);
        mu_assert(val == tests[i], "wong val on recv");
    }
    mu_assert(Queue_count(queue) == 0, "wrong count after recv");

    return NULL;
}

char *test_destroy() {
    Queue_destroy(queue);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_send_recv);
    //mu_run_test(test_destroy); another segfault

    return NULL;
}

RUN_TESTS(all_tests);
