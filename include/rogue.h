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
#include <ctype.h>

typedef void (*Ability)(struct Entity* user, struct Entity* target);

typedef struct{
  char * gfx;
  int color, known, foggy, category;
  void* parent;
} Tile;

typedef struct{
  int y,x;
  Tile t, below;
  int hp, maxhp,
    stamina, maxStamina,
    weight, maxWeight,
    visionRange;
  Ability* abilities;
  struct Room* currRoom;
  char* name;
  int dead;
} Entity;

typedef struct Room{
  int y,x,h,w;
  int type, entCount;
  Entity** ents;
} Room;

typedef struct{
  Tile ** data;
  int h,w;
  Tile fill;
  Room ** rooms;
  int roomCount;
} Map;

typedef struct{
  int h,w;
  Entity * target;
} Camera;

/*inits.c*/
void init();
Tile* initTiles();
void initColors();
/*main.c*/
void updateStats();
void delay(int milliseconds);
int range(int from, int to);
int within(int x, int from, int to);
void drawUI();
void setLog(char* text, int lineIndex);
void log(char* message);
/*maps.c*/
Map * newMap(int h, int w, Tile fill);
void drawMap();
void inscribeRoom(Room * r);
void inscribeRect(Room * r, int cornerID, int wallID, int floorID);
int collRoom(Room* r, int y, int x);
Tile* collRect(int y, int x, int h, int w, int flag);
int collEmpty(int y, int x);
Room * newRoom(int y, int x, int type);
Room ** generateDungeon(int y, int x, int maxSize);
int dungeonRoomProb();
int collEnt(Entity** ents, int ent_count, int y, int x);
void revealRoom(Room* r);
void unrevealRoom(Room* r);
Room* getRoomAt(int y, int x);
Tile getTileAt(int y, int x);
/*entities.c*/
void combat(Entity* e1, Entity* e2);
Camera * newCamera(int height, int width, Entity * target);
void handleInput(int in);
void inscribeEntity(Entity * e, Room* r);
Entity * newEntity(int y, int x, int type);
void eraseEntity(Entity* e);
void moveEntity(Entity* e, int dy, int dx);
/*abilities.c*/
void punch(Entity* user, Entity* target);
void bodySlam(Entity* user, Entity* target);
/*behaviors.c*/
void randomAI(Entity* user, Entity* target);
//

Tile* tiles;
Entity* player;
Map* currMap;
Camera* view;
char** eventLog;
int gameOver;

#endif
