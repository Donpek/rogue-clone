#ifndef ROGUE_H
#define ROGUE_H
#define MAX_STRUCTS_IN_A_SINGLE_MAP 10
#define NUM_OF_ROOM_TYPES 2

#include "ids.h"
#include "categories.h"
#include "tile_constants.h"
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int y,x,h,w;
  int type;
} Room;

typedef void (*Ability)(struct Entity* user, struct Entity** targets);

typedef struct{
  char * gfx;
  int color, visible, category;
} Tile;

typedef struct{
  int y,x;
  Tile t, below;
  int hp, maxhp, speed,
    stamina, weight,
    maxweight, visionRange;
  Ability ** abilities;
} Entity;

typedef struct{
  Tile ** data;
  int h,w;
  Tile fill;
  Room *** structs;
  Entity ** ents;
} Map;

typedef struct{
  int h,w;
  Entity * target;
} Camera;

void init();
Map * newMap(int h, int w, Tile fill);
Entity * newEntity(int y, int x, Tile tile);
void drawMap(Map * m, Camera * c);
Camera * newCamera(int height, int width, Entity * target);
void handleInput(int in, Entity * e, Map * m);
int collRoom(Map * m, int y, int x);
int collEmpty(Map * m, int y, int x);
void inscribeEntity(Entity * e, Map * m);
Room * newRoom(int y, int x, int type);
void inscribeRoom(Room * r, Map * m, Tile* ts);
void generateDungeon(Map * m, int y, int x, int size, Tile* ts);
Tile* initTiles();
void initColors();

#endif
