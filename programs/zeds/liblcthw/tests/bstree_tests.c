
#include "minunit.h"
#include <lcthw/bstree.h>
#include <lcthw/bstrlib.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

BSTree *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE");
struct tagbstring expect2 = bsStatic("THE VALUE");
struct tagbstring expect3 = bsStatic("THE VALUE");

static int traverse_good_cb(BSTreeNode *node) {
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    return 0;
}

static int traverse_fail_cb(BSTreeNode *node) {
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    if (traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

char *test_create() {
    map = BSTree_create(NULL);
    mu_assert(map != NULL, "Failed to create map");
    return NULL;
}

char *test_destroy() {
    BSTree_destroy(map);
    return NULL;
}

// imo these should be separate unit tests
// also too much duplication
char *test_get_set() {
    int rc = BSTree_set(map, &test1, &expect1);
    mu_assert(rc == 0, "failed to set test1");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == &expect1, "wrong value for test1");

    rc = BSTree_set(map, &test2, &expect2);
    mu_assert(rc == 0, "failed to set test2");
    result = BSTree_get(map, &test2);
    mu_assert(result == &expect2, "wrong value for test2");

    rc = BSTree_set(map, &test3, &expect3);
    mu_assert(rc == 0, "failed to set test3");
    result = BSTree_get(map, &test3);
    mu_assert(result == &expect3, "wrong value for test3");

    return NULL;
}

char *test_traverse() {
    int rc = BSTree_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "failed to traverse");
    mu_assert(traverse_called == 3, "wrong count for traverse_called");

    traverse_called = 0;
    rc = BSTree_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "failed to traverse");
    mu_assert(traverse_called == 2, "wrong count for traverse failure");

    return NULL;
}

// also way too much duplication
char *test_delete() {
    bstring deleted = (bstring)BSTree_delete(map, &test1);
    mu_assert(deleted != NULL, "got NULL on delete");
    mu_assert(deleted == &expect1, "should get test1");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == NULL, "should delete");

    deleted = (bstring)BSTree_delete(map, &test2);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect2, "Should get test2");
    result = BSTree_get(map, &test2);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring)BSTree_delete(map, &test3);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect3, "Should get test3");
    result = BSTree_get(map, &test3);
    mu_assert(result == NULL, "Should delete.");

    deleted = (bstring)BSTree_delete(map, &test3);
    mu_assert(deleted == NULL, "Should get NULL");

    return NULL;
}

char *test_fuzzing() {
    BSTree *store = BSTree_create(NULL);
    int i = 0;
    int j = 0;
    bstring numbers[100] = {NULL};
    bstring data[100] = {NULL};
    srand((unsigned int)time(NULL));

    for (i = 1; i < 100; i++) {
        int num = rand();
        numbers[i] = bformat("%d", num);
        data[i] = bformat("data %d", num);
        BSTree_set(store, numbers[i], data[i]);
    }

    for (i = 0; i < 100; i++) {
        bstring value = BSTree_delete(store, numbers[i]);
        mu_assert(value == data[i], "Failed to delete the right number");
        mu_assert(BSTree_delete(store, numbers[i]) == NULL, "should get nothing");

        for (j = i + 1; j < 99; j++) {
            bstring value = BSTree_get(store, numbers[j]);
            mu_assert(value == data[j], "failed to get the right number");
        }

        bdestroy(value);
        bdestroy(numbers[i]);
    }

    BSTree_destroy(store);

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);
    mu_run_test(test_fuzzing);

    return NULL;
}

RUN_TESTS(all_tests);
