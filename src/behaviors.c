#include "rogue.h"

void randomAI(Entity* user, Entity* target){
  int dir = range(0,9), dy=0,dx=0;
  switch(dir){
    case NORTH: dy--; break;
    case WEST: dx--; break;
    case SOUTH: dy++; break;
    case EAST: dx++; break;
    default: return;
  }
  moveEntity(user, dy, dx);
  user->y += dy; user->x += dx;
}
