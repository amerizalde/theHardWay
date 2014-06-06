<<<<<<< HEAD
=======
// if not defined
>>>>>>> 66b4d497e7619aed8d34f83813d4bc7cb347dfa2
#ifndef _ex19_h
#define _ex19_h

#include "object.h"

struct Monster
{
    Object proto;
    int hit_points;
};

typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

struct Room
{
    Object proto;
<<<<<<< HEAD
    Monster *bad_guy;
=======

    Monster *bad_guy;

>>>>>>> 66b4d497e7619aed8d34f83813d4bc7cb347dfa2
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

struct Map
{
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);
<<<<<<< HEAD

=======
>>>>>>> 66b4d497e7619aed8d34f83813d4bc7cb347dfa2
#endif
