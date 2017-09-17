#include "rogue.h"

void generateDungeon(Map * m, int y, int x, int size, Tile* ts){
  Room ** rooms = malloc(sizeof(Room *) * size);
  Room * r;
  int i, pY, pX, pH, pW, minWall, dir/*, offset*/;
  int stop=0;
  Room * start;

  *rooms = newRoom(y, x, rand() % 2);
  start = *rooms;
  inscribeRoom(*rooms, m, ts);

  for(i=1; i<size; i++){
    if(stop == 12 && start == *rooms){
      mvprintw(21, 0, "Too many rooms, dude.");
      return;
    }
    if(stop == 12) {
      stop = 0;
      rooms--;
    }
    r = newRoom(0, 0, rand() % NUM_OF_ROOM_TYPES);
    pY = (*rooms)->y; pX = (*rooms)->x;
    pH = (*rooms)->h; pW = (*rooms)->w;
    dir = rand() % 4;
    switch(dir){
      case 0: //EAST
        if(
          collRoom(m, pY, pX+pW) == 0 &&
          collRoom(m, pY+r->h-1, pX+pW) == 0 &&
          collRoom(m, pY, pX+pW+r->w-1) == 0 &&
          collRoom(m, pY+r->h-1, pX+pW+r->w-1) == 0 &&
          collRoom(m, pY+r->h/2-1, pX+pW+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY; r->x = pX + pW - 1;
          minWall = (r->h < (*rooms)->h) ? r->h : (*rooms)->h;
          rooms++; *rooms = r;
          inscribeRoom(r, m, ts);
          m->data[r->y+rand()%(minWall-2)+1][r->x] = ts[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 1: //NORTH
        if(
          collRoom(m, pY-r->h, pX) == 0 &&
          collRoom(m, pY-r->h, pX+r->w-1) == 0 &&
          collRoom(m, pY-1, pX) == 0 &&
          collRoom(m, pY-1, pX+r->w-1) == 0 &&
          collRoom(m, pY-r->h/2, pX+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY-r->h+1; r->x = pX;
          minWall = (r->w < (*rooms)->w) ? r->w : (*rooms)->w;
          rooms++; *rooms = r;
          inscribeRoom(r, m, ts);
          m->data[r->y+r->h-1][r->x+rand()%(minWall-2)+1] = ts[HORIZONTAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 2: //WEST
        if(
          collRoom(m, pY, pX-r->w) == 0 &&
          collRoom(m, pY, pX-1) == 0 &&
          collRoom(m, pY+r->h-1, pX-r->w) == 0 &&
          collRoom(m, pY+r->h-1, pX-1) == 0 &&
          collRoom(m, pY+r->h/2-1, pX-r->w/2) == 0
        ){
          stop=0;
          r->y = pY; r->x = pX-r->w+1;
          minWall = (r->h < (*rooms)->h) ? r->h : (*rooms)->h;
          rooms++; *rooms = r;
          inscribeRoom(r, m, ts);
          m->data[r->y+rand()%(minWall-2)+1][r->x+r->w-1] = ts[VERTICAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
      case 3: //SOUTH
        if(
          collRoom(m, pY+pH, pX) == 0 &&
          collRoom(m, pY+pH+r->h-1, pX) == 0 &&
          collRoom(m, pY+pH, pX+r->w-1) == 0 &&
          collRoom(m, pY+pH+r->h-1, pX+r->w-1) == 0 &&
          collRoom(m, pY+r->h/2-1, pX+r->w/2-1) == 0
        ){
          stop=0;
          r->y = pY+pH-1; r->x = pX;
          minWall = (r->w < (*rooms)->w) ? r->w : (*rooms)->w;
          rooms++; *rooms = r;
          inscribeRoom(r, m, ts);
          m->data[r->y][r->x+rand()%(minWall-2)+1] = ts[HORIZONTAL_DOOR_ID];}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
    }//switch
  }//for
}
void inscribeRoom(Room * r, Map * m, Tile* ts){
  int y,x,h,w;
  switch(r->type){
    case 0:
    case 1: // Rectangles
      h = r->y + r->h - 1;
      w = r->x + r->w - 1;
      m->data[r->y][r->x] = ts[CORNER_ID];
      m->data[r->y][w] = ts[CORNER_ID];
      m->data[h][r->x] = ts[CORNER_ID];
      m->data[h][w] = ts[CORNER_ID];
      for(y=1; y<r->h-1; y++){
        m->data[r->y+y][r->x] = ts[WALL_ID];
        m->data[r->y+y][w] = ts[WALL_ID];
      }
      for(x=1; x<r->w-1; x++){
        m->data[r->y][r->x+x] = ts[WALL_ID];
        m->data[h][r->x+x] = ts[WALL_ID];
      }
      for(y=1; y<r->h-1; y++){
        for(x=1; x<r->w-1; x++){
          m->data[r->y+y][r->x+x] = ts[FLOOR_ID];
        }
      }
      break;
  }
}
Room * newRoom(int y, int x, int type){
  Room * r = malloc(sizeof(Room));
  r->y = y;
  r->x = x;
  r->type = type;
  switch(type){
    case 0: //smallRect
      r->h = rand() % 6 + 3;
      r->w = rand() % 9 + 3;
      break;
    case 1: //largeRect
      r->h = rand() % 6 + 9;
      r->w = rand() % 9 + 9;
      break;
  }
  return r;
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
  m->structs = malloc(sizeof(Room **) * MAX_STRUCTS_IN_A_SINGLE_MAP);
  return m;
}
void drawMap(Map * m, Camera * c){
  int y,x;
  int cameraY = c->target->y - c->h/2;
  int cameraX = c->target->x - c->w/2;
  int offsetY = 0; int offsetX = 0;

  if(cameraY < 0){
    offsetY = -cameraY;}
  else if(cameraY + c->h > m->h){
    offsetY = m->h - cameraY - c->h;}
  if(cameraX < 0){
    offsetX = -cameraX;}
  else if(cameraX + c->w > m->w){
    offsetX = m->w - cameraX - c->w;}

  for(y=0; y<c->h; y++){
    for(x=0; x<c->w; x++){
      if(m->data[cameraY+offsetY+y][cameraX+offsetX+x].visible == 1){
        attron(COLOR_PAIR(
          m->data[cameraY+offsetY+y][cameraX+offsetX+x].color)
        );
        mvprintw(
          y,
          x,
          m->data[cameraY+offsetY+y][cameraX+offsetX+x].gfx
        );
        attroff(COLOR_PAIR(
          m->data[cameraY+offsetY+y][cameraX+offsetX+x].color)
        );}
      else
        mvprintw(y,x," ");
    }
  }
}
int collRoom(Map * m, int y, int x){
  if(x < 0 || y < 0 || x >= m->w || y >= m->h){
    return -1; // OUT OF BOUNDS
  }
  char * t = m->data[y][x].gfx;
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
int collEmpty(Map * m, int y, int x){
  if(x < 0 || y < 0 || x >= m->w || y >= m->h){
    return -1; // OUT OF BOUNDS
  }
  char * t = m->data[y][x].gfx;
  if(strcmp(t, FLOOR_GFX) == 0 ||
     strcmp(t, VERTICAL_DOOR_GFX) == 0 ||
     strcmp(t, HORIZONTAL_DOOR_GFX) == 0 ||
     strcmp(t, GRASS_GFX) == 0
  ){
    return 1;
  }
  else return 0;
}
