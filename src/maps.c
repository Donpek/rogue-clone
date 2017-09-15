#include "rogue.h"

void generateDungeon(Map * m, int y, int x, int size){
  Room ** rooms = malloc(sizeof(Room *) * size);
  Room * r;
  int i, pY, pX, pH, pW, minWall, dir/*, offset*/;
  int stop=0;
  Room * start;

  *rooms = newRoom(y, x, rand() % 2);
  start = *rooms;
  inscribeRoom(*rooms, m);

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
          inscribeRoom(r, m);
          m->data[r->y+rand()%(minWall-2)+1][r->x] = VERTICAL_DOOR;}
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
          inscribeRoom(r, m);
          m->data[r->y+r->h-1][r->x+rand()%(minWall-2)+1] = HORIZONTAL_DOOR;}
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
          inscribeRoom(r, m);
          m->data[r->y+rand()%(minWall-2)+1][r->x+r->w-1] = VERTICAL_DOOR;}
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
          inscribeRoom(r, m);
          m->data[r->y][r->x+rand()%(minWall-2)+1] = HORIZONTAL_DOOR;}
        else{
          i--;
          free(r);
          stop++;
        }
        break;
    }//switch
  }//for
}
void inscribeRoom(Room * r, Map * m){
  int y,x,h,w;
  switch(r->type){
    case 0:
    case 1: // Rectangles
      h = r->y + r->h - 1;
      w = r->x + r->w - 1;
      m->data[r->y][r->x] = UPPER_LEFT_CORNER;
      m->data[r->y][w] = UPPER_RIGHT_CORNER;
      m->data[h][r->x] = LOWER_LEFT_CORNER;
      m->data[h][w] = LOWER_RIGHT_CORNER;
      for(y=1; y<r->h-1; y++){
        m->data[r->y+y][r->x] = WESTERN_WALL;
        m->data[r->y+y][w] = EASTERN_WALL;
      }
      for(x=1; x<r->w-1; x++){
        m->data[r->y][r->x+x] = NORTHERN_WALL;
        m->data[h][r->x+x] = SOUTHERN_WALL;
      }
      for(y=1; y<r->h-1; y++){
        for(x=1; x<r->w-1; x++){
          m->data[r->y+y][r->x+x] = FLOOR;
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
Map * newMap(int height, int width, char fill){
  Map * m = malloc(sizeof(Map));
  m->fill = fill;
  m->h = height;
  m->w = width;
  m->data = malloc(sizeof(char *) * height);
  int y,x;
  for(y=0; y<height; y++){
    m->data[y] = malloc(sizeof(char) * width);
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
      mvaddch(
        y,
        x,
        m->data[cameraY+offsetY+y][cameraX+offsetX+x]
      );
    }
  }
}
int collRoom(Map * m, int y, int x){
  if(x < 0 || y < 0 || x >= m->w || y >= m->h){
    return -1; // OUT OF BOUNDS
  }
  char t = m->data[y][x];
  if(t == FLOOR ||
     t == VERTICAL_DOOR ||
     t == HORIZONTAL_DOOR ||
     t == UPPER_LEFT_CORNER ||
     t == UPPER_RIGHT_CORNER ||
     t == LOWER_LEFT_CORNER ||
     t == LOWER_RIGHT_CORNER ||
     t == WESTERN_WALL ||
     t == EASTERN_WALL ||
     t == NORTHERN_WALL ||
     t == SOUTHERN_WALL
  ){
    return 1;
  }
  else return 0;
}
int collEmpty(Map * m, int y, int x){
  if(x < 0 || y < 0 || x >= m->w || y >= m->h){
    return -1; // OUT OF BOUNDS
  }
  char t = m->data[y][x];
  if(t == FLOOR ||
     t == GRASS ||
     t == VERTICAL_DOOR ||
     t == HORIZONTAL_DOOR
  ){
    return 1;
  }
  else return 0;
}
