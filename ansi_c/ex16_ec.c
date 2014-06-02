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

void identity(struct Person who)
{
    // \t inserts a tabstop
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char const *argv[])
{
    struct Person joe = {"Joe Alex", 32, 64, 140};
    struct Person frank = {"Frank Blank", 20, 72, 180};

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &joe);
    identity(joe);
    printf("Frank is at memory location %p:\n", &frank);
    identity(frank);

    // make everyone age 20 more years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    identity(joe);

    frank.age += 20;
    frank.weight += 20;
    identity(frank);

    return 0;
}
