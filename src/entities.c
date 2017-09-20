#include "rogue.h"

void inscribeEntity(Entity * e, Room* r){
  e->below = currMap->data[e->y][e->x];
  currMap->data[e->y][e->x] = e->t;
  e->currRoom = r;
}
Camera * newCamera(int height, int width, Entity * target){
  Camera * c = malloc(sizeof(Camera));
  c->h = height;
  c->w = width;
  c->target = target;
  return c;
}
void handleInput(int in){
  int dy=0,dx=0,y,x; Room* prevRoom;
  currMap->data[user->y][user->x] = user->below;
  switch(in){
    case 'W': case 'w':
      y = user->y - 1; x = user->x; dy = -1; break;
    case 'A': case 'a':
      y = user->y; x = user->x - 1; dx = -1; break;
    case 'S': case 's':
      y = user->y + 1; x = user->x; dy = 1; break;
    case 'D': case 'd':
      y = user->y; x = user->x + 1; dx = 1; break;
  }//switch

  if(collEmpty(y,x) == 1){
    user->y += dy; user->x += dx;
  }else if(collRect(y,x,1,1,CATEGORY_MONSTER) == 1){
    //TO-DO combat
  }


  user->below = currMap->data[user->y][user->x];
  currMap->data[user->y][user->x] = user->t;

  prevRoom = user->currRoom == NULL ?
    getRoomAt(user->y-2*dy,user->x-2*dx) : user->currRoom;
  user->currRoom = getRoomAt(user->y, user->x);
  if(user->currRoom != NULL){
      unrevealRoom(prevRoom);
      revealRoom(user->currRoom);
      user->below.known = 1;
      user->below.foggy = 0;
      user->t.known = 1;
      user->t.foggy = 0;}
  else if(dx != 0 || dy != 0
  /*    this IF prevents a segfault when walking
        into walls whilst being in a door   */){
    revealRoom(getRoomAt(user->y + dy, user->x + dx));
  }//ifelse
}
void eraseEntity(Entity* e){
  currMap->data[e->y][e->x] = e->below;
  //TO-DO drop items
  eventLog = "* %s has died.", e->name;
  free(e);
}
Entity * newEntity(int y, int x, int type){
  Entity * e = malloc(sizeof(Entity));
  int i; char* name;
  e->y = y;
  e->x = x;
  e->t = tiles[type];
  switch(type){
    case PLAYER_ID:
      name = userName;
      for(i=0; i<name[i] != 0; i++){
        name[i] = toupper(name[i]);}
      e->name = name;
      e->hp = range(60, 140);
      e->maxhp = e->hp;
      e->stamina = range(12, 28);
      e->maxStamina = e->stamina;
      e->visionRange = range(6, 14);
      e->weight = range(e->hp * .7, e->hp * 1.3);
      e->maxWeight = e->weight * 1.5;
      e->abilities = malloc(sizeof(Ability) * 4);
      e->abilities[0] = punch;
      break;
    case SLIME_ID:
      e->name = "SLIME";
      e->hp = range(5, 15);
      e->maxhp = e->hp;
      e->stamina = range(1, 5);
      e->maxStamina = e->stamina;
      e->weight = e->hp;
      e->maxWeight = e->weight * 2;
      e->abilities = malloc(sizeof(Ability));
      e->abilities[0] = bodySlam;
      break;
    default:
      endwin();
      printf("newEntity type non-existant.");
  }
  return e;
}
