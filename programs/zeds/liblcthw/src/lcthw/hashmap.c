
#undef NDEBUG // why?
#include <stdint.h>
#include <lcthw/hashmap.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b) {
    return bstrcmp((bstring)a, (bstring)b);
}

// Bob Jenkins's hash algorithm
// turn the val into an uint32_t
static uint32_t default_hash(void *a) {
    size_t len = blength((bstring)a);
    char *key = bdata((bstring)a);
    uint32_t hash = 0;
    uint32_t i = 0;

    for (hash = i = 0; i < len; ++i) { // why i=0?
        hash += key[i]; // through the string
        hash += (hash << 10); // add-assign and bit shift the cur val
        hash ^= (hash >> 6); // raise-assign and bit shift the cur val
    }

    // more bit shifting and shit
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash) {
    Hashmap *map = calloc(1, sizeof(Hashmap));
    check_mem(map);

    // if params NULL then use defaults else initialise
    map->compare = compare == NULL ? default_compare : compare;
    map->hash = hash == NULL ? default_hash : hash;
    // check semantics of DArrays for a refresh...
    map->buckets = DArray_create(sizeof(DArray *), DEFAULT_NUMBER_OF_BUCKETS);
    map->buckets->end = map->buckets->max; // fake expansion of DArray
    check_mem(map->buckets);

    return map;
error:
    if (map) {
        Hashmap_destroy(map);
    }
    return NULL;
}

void Hashmap_destroy(Hashmap *map) {
    int i = 0;
    int j = 0;

    if (map) {
        if (map->buckets) {
            // free all buckets (an array of arrays)
            for (i = 0; i < DArray_count(map->buckets); i++) {
                DArray *bucket = DArray_get(map->buckets, i);
                if (bucket) {
                    // since each bucket is itself a darray, free all elements
                    for (j = 0; j < DArray_count(bucket); j++) {
                        free(DArray_get(bucket, j));
                    }
                    // then destroy it
                    DArray_destroy(bucket);
                }
            }
            // then destroy all
            DArray_destroy(map->buckets);
        }
        // and then free the map struct
        free(map);
    }
}

// a node has a hash, a key and data
static inline HashmapNode *Hashmap_node_create(int hash, void *key, void *data) {
    HashmapNode *node = calloc(1, sizeof(HashmapNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->hash = hash;

    return node;
error:
    return NULL;
}

// a bucket is a DArray...
static inline DArray *Hashmap_find_bucket(Hashmap *map, void *key, int create,
    uint32_t *hash_out) {

    uint32_t hash = map->hash(key);
    int bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS; // remainder > 0?
    check(bucket_n > 0, "invalid bucket found: %d", bucket_n);
    *hash_out = hash; // store for the return (then caller can use it)

    DArray *bucket = DArray_get(map->buckets, bucket_n);

    // why this?
    if (!bucket && create) {
        // new bucket set up
        bucket = DArray_create(sizeof(void *), DEFAULT_NUMBER_OF_BUCKETS);
        check_mem(bucket);
        DArray_set(map->buckets, bucket_n, bucket);
    }
    return bucket;
error:
    return NULL;
}

int Hashmap_set(Hashmap *map, void *key, void *data) {
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 1, &hash);
    check(bucket, "error: cannot create bucket");

    HashmapNode *node = Hashmap_node_create(hash, key, data);
    check_mem(node);
    // put the node inside the array
    DArray_push(bucket, node);

    return 0;
error:
    return -1;
}

static inline int Hashmap_get_node(Hashmap *map, uint32_t hash, DArray *bucket, void *key) {
    int i = 0;
    for (i = 0; i < DArray_end(bucket); i++) {
        debug("TRY: %d", i);
        HashmapNode *node = DArray_get(bucket, i);
        if (node->hash == hash && map->compare(node->key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void *Hashmap_get(Hashmap *map, void *key) {
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1) return NULL;

    HashmapNode *node = DArray_get(bucket, i);
    check(node != NULL, "failed to get node from bucket when it should exist");

    return node->data;
error:
    return NULL;
}

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb) {
    int i = 0;
    int j = 0;
    int rc = 0;

    for (i = 0; i < DArray_count(map->buckets); i++) {
        DArray *bucket = DArray_get(map->buckets, i);
        if (bucket) {
            for (j = 0; j < DArray_count(bucket); j++) {
                HashmapNode *node = DArray_get(bucket, j);
                rc = traverse_cb(node);
                if (rc != 0) return rc;
            }
        }
    }
    return 0;
}

void *Hashmap_delete(Hashmap *map, void *key) {
    uint32_t hash = 0;
    DArray *bucket = Hashmap_find_bucket(map, key, 0, &hash);
    if (!bucket) return NULL;

    int i = Hashmap_get_node(map, hash, bucket, key);
    if (i == -1) return NULL;

    HashmapNode *node = DArray_get(bucket, i);
    void *data = node->data;
    free(node);

    HashmapNode *ending = DArray_pop(bucket);

    if (ending != node) {
        // looks like it is not the last one, swap it
        DArray_set(bucket, i, ending);
    }
    return data;
}
