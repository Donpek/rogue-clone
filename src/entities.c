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
  int dy=0,dx=0; Room* prevRoom;
  switch(in){
    case 'W': case 'w': dy = -1; break;
    case 'A': case 'a': dx = -1; break;
    case 'S': case 's': dy = 1; break;
    case 'D': case 'd': dx = 1; break;
  }//switch

  currMap->data[player->y][player->x] = player->below;

  Tile* hit; Entity* hitE;
  if(collEmpty(player->y+dy,player->x+dx) == 1){
    player->y += dy; player->x += dx;

    prevRoom = player->currRoom == NULL ?
      getRoomAt(player->y-2*dy,player->x-2*dx) : player->currRoom;
    player->currRoom = getRoomAt(player->y, player->x);
    if(player->currRoom != NULL){
        unrevealRoom(prevRoom);
        revealRoom(player->currRoom);
        player->below.known = 1;
        player->below.foggy = 0;
        player->t.known = 1;
        player->t.foggy = 0;}
    else if(dx != 0 || dy != 0
    /*    this IF prevents a segfault when walking
          into walls whilst being in a door  */ ){
      revealRoom(getRoomAt(player->y + dy, player->x + dx));
    }//ifelse
  }else if((hit =
    collRect(player->y+dy,player->x+dx,1,1,CATEGORY_MONSTER)) != NULL)
  {
    hitE = (Entity*)(hit->parent);

    combat(player, hitE);
    mvprintw(view->h+6,1,"              ");
    mvprintw(view->h+6,1,"HP: %d SP: %d",hitE->hp,hitE->stamina);
  }

  player->below = currMap->data[player->y][player->x];
  currMap->data[player->y][player->x] = player->t;
}
void combat(Entity* e1, Entity* e2){
  e1->abilities[0](e1, e2);
  if(e2->hp > 0){
    e2->abilities[0](e2, e1);
  }
}
void updateStats(){
  int i,j; Entity* e;
  for(i=0; i<currMap->roomCount; i++){
    for(j=0; j<currMap->rooms[i]->entCount; j++){
      e = currMap->rooms[i]->ents[j];
      if(e->maxStamina > e->stamina){
        e->stamina++;}
    }
  }
  if(player->maxStamina > player->stamina){
    player->stamina++;}
}
void eraseEntity(Entity* e){
  currMap->data[e->y][e->x] = e->below;
  //TO-DO drop items
  //eventLog = "* %s has died.", e->name;
  if(e->t.category == CATEGORY_PLAYER){
    gameOver=1;
    log("You have died.");}
  else{
    free(e);}
}
Entity * newEntity(int y, int x, int type){
  Entity * e = malloc(sizeof(Entity));
  e->y = y;
  e->x = x;
  e->t = tiles[type];
  switch(type){
    case PLAYER_ID:
      e->name = userName;
      e->hp = range(60, 140);
      e->maxhp = e->hp;
      e->stamina = range(25, 50);
      e->maxStamina = e->stamina;
      e->visionRange = range(6, 14);
      e->weight = range(e->hp * .7, e->hp * 1.3);
      e->maxWeight = e->weight * 1.5;
      e->abilities = malloc(sizeof(Ability*) * 4);
      e->abilities[0] = &punch;
      break;
    case SLIME_ID:
      e->name = "SLIME";
      e->hp = range(5, 15);
      e->maxhp = e->hp;
      e->stamina = range(1, 5);
      e->maxStamina = e->stamina;
      e->weight = e->hp;
      e->maxWeight = e->weight * 2;
      e->abilities = malloc(sizeof(Ability*));
      e->abilities[0] = &bodySlam;
      break;
    default:
      endwin();
      printf("newEntity type non-existant.");
  }
  e->t.parent = (void*)e;
  return e;
}
