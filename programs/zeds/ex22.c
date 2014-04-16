#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 100;
static int THE_AGE = 37; // static at the file level (not used from other files)

int get_age() {
    return THE_AGE;
}

void set_age(int age) {
    // make static variable accessible to users of the func
    THE_AGE = age;
}

double update_ratio(double new_ratio) {
    static double ratio = 1.0; // static at func level
    double old_ratio = ratio;
    ratio = new_ratio;
    return old_ratio;
}

void print_size() {
    log_info("I think size is: %d", THE_SIZE);
}
