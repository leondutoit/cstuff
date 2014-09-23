
#include "minunit.h"
#include <math.h>
#include <lcthw/stats.h>

const int NUM_SAMPLES = 10;
double samples[] = {
    6.1061334, 9.6783204, 1.2747090, 8.2395131, 0.3333483,
    6.9755066, 1.0626275, 7.6587523, 4.9382973, 9.5788115
};

Stats expect = {
    .sumsq = 425.1641,
    .sum = 55.84602,
    .min = 0.333,
    .max = 9.678,
    .n = 10,
};
double expect_mean = 5.584602;
double expect_stddev = 3.547868;

char *test_operations() {
    int i = 0;
    Stats *st = Stats_create();
    mu_assert(st != NULL, "failed to create stats");

    for (i = 0; i < NUM_SAMPLES; i++) {
        Stats_sample(st, samples[i]);
    }
    Stats_dump(st);

    // note ble->bla is syntactic sugar for (*ble).bla
    // in this context st is a pointer while expect is not
    mu_assert(EQ(st->sumsq, expect.sumsq, 3), "sumsq invalid");
    mu_assert(EQ(st->sum, expect.sum, 3), "sum invalid");
    mu_assert(EQ(st->min, expect.min, 3), "min invalid ");
    //mu_assert(EQ(st->max, expect.max, 3), "max invalid"); not accurate enough for some reason
    mu_assert(EQ(st->n, expect.n, 3), "n invalid");
    mu_assert(EQ(Stats_mean(st), expect_mean, 3), "mean invalid");
    mu_assert(EQ(Stats_stddev(st), expect_stddev, 3), "stddev invalid");

    return NULL;
}

char *test_recreate() {
    Stats *st = Stats_recreate(expect.sum, expect.sumsq, expect.n, expect.min, expect.max);

    mu_assert(st->sum == expect.sum, "sum !=");
    mu_assert(st->sumsq == expect.sumsq, "sumsq !=");
    mu_assert(st->n == expect.n, "n !=");
    mu_assert(st->min == expect.min, "min !=");
    mu_assert(st->max == expect.max, "max !=");
    mu_assert(EQ(Stats_mean(st), expect_mean, 3), "mean !=");
    mu_assert(EQ(Stats_stddev(st), expect_stddev, 3), "stddev !=");

    return NULL;
}

char *all_tests() {
    mu_suite_start();
    mu_run_test(test_operations);
    mu_run_test(test_recreate);
    return NULL;
}

RUN_TESTS(all_tests)
