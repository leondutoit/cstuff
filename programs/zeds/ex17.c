#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512 // constants (uses the pre-processor CPP)
#define MAX_ROWS 100

// heap ~ remaining mem; get some with malloc; returns a pointer
// return the piece to the OS with free

// stack ~ function local storage
// C compiler pops vars off the stack when function returns
// prevents mem leaks

// potential mem problems
// if you get mem from malloc, and have the pointer on the stack
// you will lose it when the function exits
// stack overflow
// segfault, segmentation fault
// - take a pointer to something on the stack, return it from a function
// then the receiver will segfault because the actual data will get popped off



struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file; // FILE is also a struct
    struct Database *db;
};

// TODO (Leon)
void create_addresses(struct Connection *conn, int max_data, int max_rows) {
    // make a prototype address and accept params for initial size
    int i = 0;
    for (i = 0; i < max_rows; i++) {
        struct Address addr = {.id = i, .set = 0};
        conn->db->rows[i] = addr; // use the conn to set the row in the db
        printf("Row in db %d\n", i);
    }
}

void Database_close(struct Connection *conn); // declare before define

void die(const char *message, struct Connection *conn) {
    Database_close(conn);
    if (errno) {
        perror(message); // print a sys error message
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1); // abort and let the OS clean up for you
}

void Address_print(struct Address *addr) {
    printf("%d %s %s\n",
        addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn) {
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load db.", conn);
}

// a pointer function coz ur returning a pointer
struct Connection *Database_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database)); // on the heap
    if (!conn->db) die("Memory error", conn);

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load(conn);
        }
    }
    if (!conn->file) die("Failed to open file", conn);

    return conn;
}

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file); // reposition a stream - sets it to beginning
    // writes binary stream (source ptr, size, nmemb elements of data, stream)
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to write to db", conn); // rc = number of items written

    rc = fflush(conn->file); // forces a write of all user-space buffered data
    if (rc == -1) die("Cannot flush db", conn);
}

// create the whole thing in one go
void Database_create(struct Connection *conn) {
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialise it
        struct Address addr = {.id = i, .set = 0};
        // assign it (copy prototype)
        conn->db->rows[i] = addr;
    }
}

void Database_create_with_params(struct Connection *conn, int max_data, int max_rows) {

    create_addresses(conn, max_data, max_rows);

}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;
    // WARNING: bug here must fix
    // strncpy does not include string termination
    // can be a problem if not enough data in reciever
    //char *res = strncpy(addr->name, name, MAX_DATA);
    char *res = strcpy(addr->name, name);
    // demonstrate strncpy bug
    if (!res) die("Name copy failed", conn);
    // strncpy(destination, source, max_size)
    //res = strncpy(addr->email, email, MAX_DATA);
    res = strcpy(addr->name, name);
    if (!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id]; // get the address

    if (addr->set) {
        Address_print(addr);
    } else {
        die("Id is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];
        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {

    // get command args
    if (argc < 3) {
        printf(
            "USAGE: ./ex17 <db_file_name> <action> [action params]\n");
        exit(1);
    }

    int data;
    int rows;
//   int max_rows = MAX_ROWS;
//    int max_data = MAX_DATA;
    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]); // convert string to int
    if (id >= MAX_ROWS) die("There are not that many records", conn);

    switch (action) {

        case 'c':
            int data = argv[3];
            int rows = argv[4];
            Database_create_with_params(conn, data, rows);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die("Need an id to get", conn);
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("need id, name, email to set", conn);
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die("Need id to delete", conn);
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid aciton, only: c = create, g = get, s = set, d = del, l = list",
                conn);
    }

    Database_close(conn);

    return 0;
}
