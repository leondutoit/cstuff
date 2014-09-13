
#ifndef string_algos_h
#define string_algos_h

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>

// to keep state
typedef struct StringScanner {
    bstring in;
    const unsigned char *haystack; // what to search through
    ssize_t hlen; //  haystack length I presume
    const unsigned char *needle; // what to search for
    ssize_t nlen; // needle length I also presume
    size_t skip_char[UCHAR_MAX + 1];
} StringScanner;

int String_find(bstring in, bstring what);
StringScanner *StringScanner_create(bstring in);
int StringScanner_scan(StringScanner *scan, bstring tofind);
void StringScanner_destroy(StringScanner *scan);

#endif
