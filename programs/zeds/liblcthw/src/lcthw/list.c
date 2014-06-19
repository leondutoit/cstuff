
#include "list.h"
#include "dbg.h"

List *List_create() {
    return calloc(1, sizeof(List));
}

void List_destroy(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);
}

void List_clear(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List *list) {
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value) {
    // create a new node
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    // set the value
    node->value = value;

    if (list->last == NULL) {
        // if this is the first element
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node; // point to new from current last
        node->prev = list->last; // point to previous last from new last
        list->last = node; // set last to point to new element
    }
    list->count++;

error:
    return;
}

void *List_pop(List *list) {
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value) {
    // add value to beginning of the list
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        // is this the first element?
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->count++;

error:
    return;
}

void *List_shift(List *list) {
    // remove first value of the list
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node) {
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node cannot be NULL.");

    if (node == list->first && node == list->last) {
        // only list element
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        // removing the first element
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got NULL first element.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        // removing the last element
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got NULL last element.");
        list->last->next = NULL;
    } else {
        // removing a random element (move pointers 'over' current element)
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }
    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}
