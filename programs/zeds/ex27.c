#undef NDEBUG
#include "dbg.h"
#include <stdio.h>
#include <assert.h>

/*
 * Naive copy: assumes input always valid.
 */
void copy(char *to[], char *from[]) {
    int i = 0;
    // will not end unless '\0' terminated!
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

/*
 * Safer copy: checks for common errors
 * using string length to control loops and termination.
 */
int safercopy(int from_len, char *from, int to_len, char *to) {
    // put helpful debug message in assert (trick)
    assert(from != NULL && to != NULL && "from and to can't be NULL");
    int i = 0;
    int max = from_len > to_len - 1 ? to_len : from_len;

    // to_len must have at least one byte
    if (from_len < 0 || to_len <= 0) return -1;

    for (i = 0; i < max; i++) {
        to[i] = from[i];
    }

    to[to_len - 1] = '\0';

    return i;
}

int main(int argc, char *argv[]) {
    char from[] = "0123456789";
    int from_len = sizeof(from);

    char to[] = "0123456";
    int to_len = sizeof(to);

    debug("Copying '%s':%d to '%s':%d", from, from_len, to, to_len);

    int rc = safercopy(from_len, from, to_len, to);
    check(rc > 0, "Failed to copy.");
    check(to[to_len - 1] == '\0', "String not terminated.");

    rc = safercopy(from_len, from, 0, to);
    check(rc == -1, "safercopy should fail #2.");
    check(to[to_len - 1] == '\0', "String not terminated.");

    return 0;
error:
    return 1;
}
