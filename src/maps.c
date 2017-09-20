#include "rogue.h"

int dungeonRoomProb(){
  int roll = range(1,100);
  if(roll <= 20){
    return SLIME_ROOM;
  }else if(roll <= 60){
    return SMALL_RECTANGLE;
  }else
    return LARGE_RECTANGLE;
}

Room** generateDungeon(int y, int x, int maxSize){
  Room ** rooms = malloc(sizeof(Room *) * maxSize);
  Room * r;
  int i, pY, pX, pH, pW, minWall, dir;
  int stop=0, currIndex=0, size=1;
  Room * start;

  rooms[0] = newRoom(y, x, dungeonRoomProb());
  start = rooms[0];
  currMap->roomCount++;
  inscribeRoom(rooms[0]);

  for(i=1; i<maxSize; i++){
    if(stop == 24 && rooms[currIndex] == start){return rooms;}
    if(stop == 24) {
      stop = 0;
      currIndex--;
    }
    r = newRoom(0, 0, dungeonRoomProb());
    pY = rooms[currIndex]->y; pX = rooms[currIndex]->x;
    pH = rooms[currIndex]->h; pW = rooms[currIndex]->w;
    dir = rand() % 4;
    switch(dir){
      case 0: //EAST
        if(!collRect(pY, pX+pW, r->h, r->w, CATEGORY_ROOM)){
          stop=0;
          r->y = pY; r->x = pX + pW - 1;
          minWall = (r->h < pH) ?
            r->h : pH;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+rand()%(minWall-2)+1][r->x] =
            tiles[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 1: //NORTH
        if(!collRect(pY-r->h,pX,r->h,r->w,CATEGORY_ROOM)){
          stop=0;
          r->y = pY-r->h+1; r->x = pX;
          minWall = (r->w < pW) ?
            r->w : pW;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+r->h-1][r->x+rand()%(minWall-2)+1] =
            tiles[HORIZONTAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 2: //WEST
        if(!collRect(pY,pX-r->w,r->h,r->w,CATEGORY_ROOM)){
          stop=0;
          r->y = pY; r->x = pX-r->w+1;
          minWall = (r->h < rooms[currIndex]->h) ?
            r->h : rooms[currIndex]->h;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y+rand()%(minWall-2)+1][r->x+r->w-1] =
            tiles[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 3: //SOUTH
        if(!collRect(pY+pH,pX,r->h,r->w,CATEGORY_ROOM)){
          stop=0;
          r->y = pY+pH-1; r->x = pX;
          minWall = (r->w < pW) ?
            r->w : pW;
          currIndex++; rooms[size] = r;
          currMap->roomCount++; size++;
          inscribeRoom(r);
          currMap->data[r->y][r->x+rand()%(minWall-2)+1] =
            tiles[HORIZONTAL_DOOR_ID];}
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
      r->h = range(4, 7);
      r->w = range(6, 9);
      break;
    case LARGE_RECTANGLE:
      r->h = range(5,9);
      r->w = range(10,18);
      break;
    case SLIME_ROOM:
      r->h = range(4, 7);
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
      y > r->y && y < r->y + r->h-1
      &&
      x > r->x && x < r->x + r->w-1
    ){return r;}
  }
  return NULL;
}
Tile getTileAt(int y, int x){
  return currMap->data[y][x];
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
  for(y=1; y<view->h+1; y++){
    for(x=1; x<view->w+1; x++){
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
int collRect(int y, int x, int h, int w, int flag){
  int j,k; Tile t;
  int jl=y+h, kl=x+w;
  for(j=y; j<jl; j++){
    for(k=x; k<kl; k++){
      if(k < 0 || j < 0 || k >= currMap->w || j >= currMap->h){
        return -1; /*OUT OF BOUNDS*/}
      else{
        t = currMap->data[j][k];
        if(t.category == flag){
          return 1;
        }
      }
    }
  }
  return 0;
}
int collRoom(Room* r, int y, int x){
  if(x < 0 || y < 0 || x >= currMap->w || y >= currMap->h){
    return -1; // OUT OF BOUNDS
  }
  int j,k; char* t;
  for(j=y; j<y+r->h; j++){
    for(k=x; k<x+r->w; k++){
      t = currMap->data[j][k].gfx;
      if(
        strcmp(t, FLOOR_GFX) == 0 ||
        strcmp(t, VERTICAL_DOOR_GFX) == 0 ||
        strcmp(t, HORIZONTAL_DOOR_GFX) == 0 ||
        strcmp(t, CORNER_GFX) == 0 ||
        strcmp(t, WALL_GFX) == 0
      ){
        return 1;
      }
    }
  }
  return 0;
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
      currMap->data[y][x].known=1;
      currMap->data[y][x].foggy=0;
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
