#include "rogue.h"

void inscribeEntity(Entity * e, Map * m){
  e->below = m->data[e->y][e->x];
  m->data[e->y][e->x] = e->gfx;
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
      if(coll(m, e->y - 1, e->x) == 'N') e->y--; break;
    case 'A':
    case 'a':
      if(coll(m, e->y, e->x - 1) == 'N') e->x--; break;
    case 'S':
    case 's':
      if(coll(m, e->y + 1, e->x) == 'N') e->y++; break;
    case 'D':
    case 'd':
      if(coll(m, e->y, e->x + 1) == 'N') e->x++; break;
  }//switch
  e->below = m->data[e->y][e->x];
  m->data[e->y][e->x] = e->gfx;
}
Entity * newEntity(int y, int x, char graphic){
  Entity * e = malloc(sizeof(Entity));
  e->y = y;
  e->x = x;
  e->gfx = graphic;
  return e;
}
