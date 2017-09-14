#ifndef ROGUE_H
#define ROGUE_H
#define MAX_STRUCTS_IN_A_SINGLE_MAP 10
#define NUM_OF_ROOM_TYPES 2
/*TILES*/
#define PLAYER '@'
#define GRASS '.'
/*ROOM TILES*/
#define VERTICAL_DOOR '|'
#define HORIZONTAL_DOOR '-'
#define UPPER_LEFT_CORNER 'x'
#define UPPER_RIGHT_CORNER 'x'
#define LOWER_LEFT_CORNER 'x'
#define LOWER_RIGHT_CORNER 'x'
#define WESTERN_WALL 'x'
#define EASTERN_WALL 'x'
#define NORTHERN_WALL 'x'
#define SOUTHERN_WALL 'x'
#define FLOOR ' '
/**/
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
  int y,x,h,w;
  int type;
} Room;

typedef struct{
  int y,x;
  char gfx;
  char below;
} Entity;

typedef struct{
  char ** data;
  int h,w;
  char fill;
  Room *** structs;
  Entity ** ents;
} Map;

typedef struct{
  int h,w;
  Entity * target;
} Camera;

void init();
Map * newMap(int h, int w, char fill);
Entity * newEntity(int y, int x, char graphic);
void drawMap(Map * m, Camera * c);
Camera * newCamera(int height, int width, Entity * target);
void handleInput(int in, Entity * e, Map * m);
char coll(Map * m, int y, int x);
void inscribeEntity(Entity * e, Map * m);
Room * newRoom(int y, int x, int type);
void inscribeRoom(Room * r, Map * m);
void generateDungeon(Map * m, int y, int x, int numRooms);

#endif
