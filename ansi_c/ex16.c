#include <stdio.h>  // provides printf()
#include <assert.h> // provides assert()
#include <stdlib.h> // provides malloc(), free(), and NULL
#include <string.h> // provides strdup(), and also has NULL

struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    /*  malloc() allocates a chunk of memory, the size of which is measured
        by how much a struct would need based on the member variables defined
        in Person.

        assert() tests that it was created properly.
    */
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);  // there is a who

    // fill in the member variables, using the args passed to Person_create().
    who->name = strdup(name); // allocates and duplicates a string into memory.
    who->age = age;
    who->height = height;
    who->weight = weight;

    // return the new struct.
    return who;
};

void Person_destroy(struct Person *who)
{
    // assert checks for bad input
    assert(who != NULL);
    // return the memory taken for creating the struct.
    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    // \t inserts a tabstop
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char const *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
        "Joe Alex", 32, 64, 140);
    struct Person *frank = Person_create(
        "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);
    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 more years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
