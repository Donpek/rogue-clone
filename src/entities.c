#include "rogue.h"

void inscribeEntity(Entity * e, Map * m){
  e->below = m->data[e->y][e->x];
  m->data[e->y][e->x] = e->t;
}
Camera * newCamera(int height, int width, Entity * target){
  Camera * c = malloc(sizeof(Camera));
  c->h = height;
  c->w = width;
  c->target = target;
  return c;
}
void handleInput(int in, Entity * e, Map * m){
  m->data[e->y][e->x] = e->below;
  switch(in){
    case 'W':
    case 'w':
      if(collEmpty(m, e->y - 1, e->x) == 1) e->y--; break;
    case 'A':
    case 'a':
      if(collEmpty(m, e->y, e->x - 1) == 1) e->x--; break;
    case 'S':
    case 's':
      if(collEmpty(m, e->y + 1, e->x) == 1) e->y++; break;
    case 'D':
    case 'd':
      if(collEmpty(m, e->y, e->x + 1) == 1) e->x++; break;
  }//switch
  e->below = m->data[e->y][e->x];
  m->data[e->y][e->x] = e->t;
}
Entity * newEntity(int y, int x, Tile tile){
  Entity * e = malloc(sizeof(Entity));
  e->y = y;
  e->x = x;
  e->t = tile;
  return e;
}
