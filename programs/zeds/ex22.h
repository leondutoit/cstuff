#ifndef _ex_22_h
#define _ex_22_h

// make THE_SIZE variable in ex22.c available in other .c files
// tell the compiler the variable exists in another location
extern int THE_SIZE;

// get and set internal static variables in ex22.c
int get_age();
void set_age(int age);

// update a static variable inside the update_ratio
double update_ratio(double ratio);

void print_size();

#endif
