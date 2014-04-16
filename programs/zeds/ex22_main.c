#include "ex22.h"
#include "dbg.h"

// alternative to define
const char *MY_NAME = "Leon du Toit";

void scope_demo(int count) {
    log_info("count is: %d", count);
    if (count > 10) {
        int count = 100; // bugs
        log_info("count in this scope is: %d", count);
    }
    log_info("at exit count is: %d", count);
    count = 3000;
    log_info("after assign count is: %d", count);
}

int main(int argc, char *argv[]) {
    // test the_age accessors
    log_info("Name: %s, age: %d", MY_NAME, get_age());
    set_age(100);
    log_info("New age: %d", get_age());

    // test THE_SIZE extern
    log_info("The size: %d", THE_SIZE);
    print_size();
    THE_SIZE = 9;
    log_info("now the size is: %d", THE_SIZE);
    print_size();

    // test ratio function static
    log_info("at first ratio is: %f", update_ratio(2.0));
    log_info("ratio again: %f", update_ratio(10.0));
    log_info("once more: %f", update_ratio(300.0));

    // test scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling the scope_demo: %d", count);

    return 0;
}
