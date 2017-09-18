#include "rogue.h"

int dungeonRoomProb(){
  int roll = range(1,100);
  if(roll <= 10){
    return SLIME_ROOM;
  }else if(roll <= 70){
    return SMALL_RECTANGLE;
  }else
    return LARGE_RECTANGLE;
}

Room** generateDungeon(int y, int x, int maxSize){
  Room ** rooms = malloc(sizeof(Room *) * maxSize);
  Room * r;
  int i, pY, pX, pH, pW, minWall, dir;
  int stop=0, currIndex=0, size=0;
  Room * start;

  rooms[size] = newRoom(y, x, dungeonRoomProb());
  start = rooms[size];
  currMap->roomCount++;
  inscribeRoom(rooms[size]);
  size++;

  for(i=1; i<maxSize; i++){
    if(stop == 12 && start == rooms[currIndex]){
      mvprintw(21, 0, "Too many rooms, dude.");
      return rooms;
    }
    if(stop == 12) {
      stop = 0;
      currIndex--;
    }
    r = newRoom(0, 0, dungeonRoomProb());
    pY = rooms[currIndex]->y; pX = rooms[currIndex]->x;
    pH = rooms[currIndex]->h; pW = rooms[currIndex]->w;
    dir = rand() % 4;
    switch(dir){
      case 0: //EAST
        if(
          collRoom(pY, pX+pW) == 0 &&
          collRoom(pY+r->h-1, pX+pW) == 0 &&
          collRoom(pY, pX+pW+r->w-1) == 0 &&
          collRoom(pY+r->h-1, pX+pW+r->w-1) == 0 &&
          collRoom(pY+r->h/2-1, pX+pW+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY; r->x = pX + pW - 1;
          minWall = (r->h < rooms[currIndex]->h) ?
            r->h : rooms[currIndex]->h;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+rand()%(minWall-2)+1][r->x] = tiles[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 1: //NORTH
        if(
          collRoom(pY-r->h, pX) == 0 &&
          collRoom(pY-r->h, pX+r->w-1) == 0 &&
          collRoom(pY-1, pX) == 0 &&
          collRoom(pY-1, pX+r->w-1) == 0 &&
          collRoom(pY-r->h/2, pX+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY-r->h+1; r->x = pX;
          minWall = (r->w < rooms[currIndex]->w) ?
            r->w : rooms[currIndex]->w;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+r->h-1][r->x+rand()%(minWall-2)+1] = tiles[HORIZONTAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 2: //WEST
        if(
          collRoom(pY, pX-r->w) == 0 &&
          collRoom(pY, pX-1) == 0 &&
          collRoom(pY+r->h-1, pX-r->w) == 0 &&
          collRoom(pY+r->h-1, pX-1) == 0 &&
          collRoom(pY+r->h/2-1, pX-r->w/2) == 0
        ){
          stop=0;
          r->y = pY; r->x = pX-r->w+1;
          minWall = (r->h < rooms[currIndex]->h) ?
            r->h : rooms[currIndex]->h;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+rand()%(minWall-2)+1][r->x+r->w-1] = tiles[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 3: //SOUTH
        if(
          collRoom(pY+pH, pX) == 0 &&
          collRoom(pY+pH+r->h-1, pX) == 0 &&
          collRoom(pY+pH, pX+r->w-1) == 0 &&
          collRoom(pY+pH+r->h-1, pX+r->w-1) == 0 &&
          collRoom(pY+r->h/2-1, pX+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY+pH-1; r->x = pX;
          minWall = (r->w < rooms[currIndex]->w) ?
            r->w : rooms[currIndex]->w;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y][r->x+rand()%(minWall-2)+1] = tiles[HORIZONTAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
    }//switch
  }//for
  return rooms;
}
void inscribeRect(Room * r, int cornerID, int wallID, int floorID){
  int y,x,h,w;
  h = r->y + r->h - 1;
  w = r->x + r->w - 1;
  currMap->data[r->y][r->x] = tiles[cornerID];
  currMap->data[r->y][w] = tiles[cornerID];
  currMap->data[h][r->x] = tiles[cornerID];
  currMap->data[h][w] = tiles[cornerID];
  for(y=1; y<r->h-1; y++){
    currMap->data[r->y+y][r->x] = tiles[wallID];
    currMap->data[r->y+y][w] = tiles[wallID];
  }
  for(x=1; x<r->w-1; x++){
    currMap->data[r->y][r->x+x] = tiles[wallID];
    currMap->data[h][r->x+x] = tiles[wallID];
  }
  for(y=1; y<r->h-1; y++){
    for(x=1; x<r->w-1; x++){
      currMap->data[r->y+y][r->x+x] = tiles[floorID];
    }
  }
}
void inscribeRoom(Room * r){
  int y,x,h,w;
  switch(r->type){
    case SMALL_RECTANGLE:
    case LARGE_RECTANGLE: // Rectangles
      inscribeRect(r,CORNER_ID,WALL_ID,FLOOR_ID);
      break;
    case SLIME_ROOM:
     inscribeRect(r,CORNER_ID,WALL_ID,FLOOR_ID);
     for(y=0; y<r->entCount; y++){
       r->ents[y]->y += r->y;
       r->ents[y]->x += r->x;
       inscribeEntity(r->ents[y], r);
     }
     break;
  }
}
int collEnt(Entity** ents, int ent_count, int y, int x){
  int i;
  for(i=0; i<ent_count-1; i++){
    if(ents[i]->y == y && ents[i]->x == x){
      return 1;
    }
  }
  return 0;
}
Room * newRoom(int y, int x, int type){
  Room * r = malloc(sizeof(Room));
  int i;
  r->y = y;
  r->x = x;
  r->type = type;
  switch(type){
    case SMALL_RECTANGLE:
      r->h = range(6, 9);
      r->w = range(6, 9);
      break;
    case LARGE_RECTANGLE:
      r->h = range(10,18);
      r->w = range(10,18);
      break;
    case SLIME_ROOM:
      r->h = range(6, 12);
      r->w = range(6, 12);
      int y,x;
      r->entCount = range(r->h*.5,r->h*1.5);
      r->ents = malloc(sizeof(Entity*) * r->entCount);
      for(i=0; i<r->entCount; i++){
        y = range(1, r->h-2); x = range(1, r->w-2);
        if(collEnt(r->ents,i+1,y,x) == 0){
          r->ents[i] = newEntity(y,x,SLIME_ID);
        }else{
          i--;
        }
      }
      break;
  }
  return r;
}
Room* getRoomAt(int y, int x){
  int i; Room* r;
  for(i=0; i<currMap->roomCount; i++){
    r = currMap->rooms[i];
    if(
      y >= r->y && y <= r->y + r->h-1
      &&
      x >= r->x && x <= r->x + r->w-1
    ){
      mvprintw(20, 8, "                       ");
      mvprintw(20, 8, "y: %d x: %d h: %d w: %d",r->y,r->x,r->h,r->w);
      return r;
    }
  }
  endwin();
  printf("Not within a room. %d\n", currMap->roomCount);
}
Map * newMap(int height, int width, Tile fill){
  Map * m = malloc(sizeof(Map));
  m->fill = fill;
  m->h = height;
  m->w = width;
  m->data = malloc(sizeof(Tile *) * height);
  int y,x;
  for(y=0; y<height; y++){
    m->data[y] = malloc(sizeof(Tile) * width);
    for(x=0; x<width; x++){
      m->data[y][x] = fill;
    }
  }
  m->roomCount = 0;
  return m;
}
void drawMap(){
  int y,x;
  int cameraY = view->target->y - view->h/2;
  int cameraX = view->target->x - view->w/2;
  int offsetY = 0; int offsetX = 0;

  if(cameraY < 0){
    offsetY = -cameraY;}
  else if(cameraY + view->h > currMap->h){
    offsetY = currMap->h - cameraY - view->h;}
  if(cameraX < 0){
    offsetX = -cameraX;}
  else if(cameraX + view->w > currMap->w){
    offsetX = currMap->w - cameraX - view->w;}

  int color; Tile t;
  for(y=0; y<view->h; y++){
    for(x=0; x<view->w; x++){
      t = currMap->data[cameraY+offsetY+y][cameraX+offsetX+x];
      if(t.known == 1){
        if(t.foggy == 1){color = WHITE;}
        else{color = t.color;}
        attron(COLOR_PAIR(color));
        mvprintw(y,x,t.gfx);
        attroff(COLOR_PAIR(color));
      }
      else mvprintw(y,x," ");
    }
  }
}
int collRoom(int y, int x){
  if(x < 0 || y < 0 || x >= currMap->w || y >= currMap->h){
    return -1; // OUT OF BOUNDS
  }
  char * t = currMap->data[y][x].gfx;
  if(strcmp(t, FLOOR_GFX) == 0 ||
     strcmp(t, VERTICAL_DOOR_GFX) == 0 ||
     strcmp(t, HORIZONTAL_DOOR_GFX) == 0 ||
     strcmp(t, CORNER_GFX) == 0 ||
     strcmp(t, WALL_GFX) == 0
  ){
    return 1;
  }
  else return 0;
}
int collEmpty(int y, int x){
  if(x < 0 || y < 0 || x >= currMap->w || y >= currMap->h){
    return -1; // OUT OF BOUNDS
  }
  char * t = currMap->data[y][x].gfx;
  if(strcmp(t, FLOOR_GFX) == 0 ||
     strcmp(t, VERTICAL_DOOR_GFX) == 0 ||
     strcmp(t, HORIZONTAL_DOOR_GFX) == 0 ||
     strcmp(t, GRASS_GFX) == 0 ||
     strcmp(t, GRASS2_GFX) == 0
  ){
    return 1;
  }
  else return 0;
}
void revealRoom(Room* r){
  int y,x,h,w;
  h = r->h + r->y; w = r->w + r->x;
  for(y=r->y; y<h; y++){
    for(x=r->x; x<w; x++){

      if(!currMap->data[y][x].known) {
        currMap->data[y][x].known=1;
        currMap->data[y][x].foggy=0;}
      else if(currMap->data[y][x].foggy) {
        currMap->data[y][x].foggy=0;
      }
    }
  }
}
void unrevealRoom(Room* r){
  int y,x,h,w;
  h = r->h + r->y; w = r->w + r->x;
  for(y=r->y; y<h; y++){
    for(x=r->x; x<w; x++){
        currMap->data[y][x].foggy = 1;}}
}
