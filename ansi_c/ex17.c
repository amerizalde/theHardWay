#include <stdio.h>  // provides printf()
#include <assert.h> // provides assert()
#include <stdlib.h> // provides malloc(), free(), and NULL
#include <string.h> // provides strdup(), and also has NULL
#include <errno.h>  // defines macros to report error conditions through
                    // error codes stored in a static location called errno

#define MAX_DATA 512
#define MAX_ROWS 100


struct Address
{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database
{
    struct Address rows[MAX_ROWS];
};

struct Connection
{
    FILE *file;
    struct Database *db;
};

void _die(const char *message)
{
    // handle errors, with option to pass a specific message.
    if (errno)
    {
        perror(message); // print the error message.
    }
    else
    {
        printf("ERROR: %s\n", message);
    }
    exit(1); // ERROR
}

void Database_close(struct Connection *conn)
{
    if (conn)
    {
        if (conn->file)
        {
            fclose(conn->file);
        }
        if (conn->db)
        {
            free(conn->db);
        }
        free(conn);
    }
}

void die(const char *message, struct Connection *conn)
{
    _die(message);
    Database_close(conn); // free the database
    exit(1); // ERROR
}

void Address_print(struct Address *addr)
{
    // print out the address contents
    printf("%d %s %s\n",
        addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
    {
        die("Database_load: failed to load database.", conn);
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
    {
        die("Database_open: Connection: Memory Error", conn);
    }

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
    {
        die("Database_open: Database: Memory Error", conn);
    }

    if (mode == 'c')
    {
        conn->file = fopen(filename, "w");
    }
    else
    {
        conn->file = fopen(filename, "r+");
        if (conn->file)
        {
            Database_load(conn);
        }
    }

    if (!conn->file)
    {
        die("Database_open: Failed to open the file.", conn);
    }

    return conn;
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
    {
        die("Database_write: Failed to write database.", conn);
    }
    rc = fflush(conn->file);
    if (rc == -1)
    {
        die("Database_write: Cannot flush database.", conn);
    }
}

void Database_create(struct Connection *conn)
{
    int i = 0;
    for (i = 0; i < MAX_ROWS; i++)
    {
        // make a prototype to initialize it.
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set)
    {
        die("Database_set: Already set, delete it first.", conn);
    }
    addr->set = 1;
    // Warning: bug, read the "How to break it" and fix this.
    char *res = strncpy(addr->name, name, MAX_DATA);
    addr->name[MAX_DATA - 1] = '\0';  // fix?
    // demonstrate the strncpy bug.
    if (!res)
    {
        die("Database_set: Name copy failed.", conn);
    }
    res = strncpy(addr->email, email, MAX_DATA);
    if (!res)
    {
        die("Database_set: Email copy failed.", conn);
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set)
    {
        Address_print(addr);
    }
    else
    {
        die("Database_get: ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;
    for (i = 0; i < MAX_ROWS; i++)
    {
        struct Address *cur = &db->rows[i];
        if (cur->set)
        {
            Address_print(cur);
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        _die("USAGE: ./ex17 <dbfile> <action> [action params]");
    }
    char const *filename = argv[1];
    char const action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3)
    {
        id = atoi(argv[3]); // convert string arg to int
    }
    if (id >= MAX_ROWS)
    {
        die("main: There's not that many records.", conn);
    }
    switch(action)
    {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g':
            if (argc != 4)
            {
                die("main: Need an id to get.", conn);
            }
            Database_get(conn, id);
            break;
        case 's':
            if (argc != 6)
            {
                die("main: Need id, name, email to set.", conn);
            }
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        case 'd':
            if (argc != 4)
            {
                die("main: Need id to delete.", conn);
            }
            Database_delete(conn, id);
            Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die(
                "main: Invalid action, only: c=create, g=get, s=set, d=del, l=list",
                conn);
    }
    Database_close(conn);
    return 0;
}
