#include "rogue.h"

void inscribeEntity(Entity * e){
  e->below = currMap->data[e->y][e->x];
  currMap->data[e->y][e->x] = e->t;
}
Camera * newCamera(int height, int width, Entity * target){
  Camera * c = malloc(sizeof(Camera));
  c->h = height;
  c->w = width;
  c->target = target;
  return c;
}
void handleInput(int in, Entity * e){
  currMap->data[e->y][e->x] = e->below;
  switch(in){
    case 'W':
    case 'w':
      if(collEmpty(e->y - 1, e->x) == 1) e->y--; break;
    case 'A':
    case 'a':
      if(collEmpty(e->y, e->x - 1) == 1) e->x--; break;
    case 'S':
    case 's':
      if(collEmpty(e->y + 1, e->x) == 1) e->y++; break;
    case 'D':
    case 'd':
      if(collEmpty(e->y, e->x + 1) == 1) e->x++; break;
  }//switch
  e->below = currMap->data[e->y][e->x];
  currMap->data[e->y][e->x] = e->t;
}
void eraseEntity(Entity* e){
  currMap->data[e->y][e->x] = e->below;
  //TO-DO drop items
  free(e);
}
Entity * newEntity(int y, int x, int type){
  Entity * e = malloc(sizeof(Entity));
  e->y = y;
  e->x = x;
  e->t = tiles[type];
  switch(type){
    case PLAYER_ID:
      e->hp = range(60, 140);
      e->maxhp = e->hp;
      e->stamina = range(12, 28);
      e->maxStamina = e->stamina;
      e->visionRange = range(6, 14);
      e->weight = range(e->hp * .7, e->hp * 1.3);
      e->maxweight = e->weight * 1.5;
      e->abilities = malloc(sizeof(Ability) * 4);
      e->abilities[0] = punch;
      break;
    case SLIME_ID:
      e->hp = range(5, 15);
      e->maxhp = e->hp;
      e->stamina = range(1, 5);
      e->maxStamina = e->stamina;
      e->visionRange = range(2, 6);
      e->weight = e->hp;
      e->maxweight = e->weight * 2;
      e->abilities = malloc(sizeof(Ability) * 3);
      e->abilities[0] = bodySlam;
      break;
    default:
      endwin();
      printf("newEntity type non-existant.");
  }
  return e;
}
