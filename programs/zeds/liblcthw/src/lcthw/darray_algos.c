
#include <stdlib.h>
#include <lcthw/darray_algos.h>
#include <bsd/stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp) {
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

/* on linux precise need to get these from libbsd-dev */

int DArray_heapsort(DArray *array, DArray_compare cmp) {
    return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp) {
    return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}
