#include "rogue.h"

void main(){
  init();
  tiles = initTiles();
  user = newEntity(50,50,PLAYER_ID);
  currMap = newMap(100,100,tiles[GRASS_ID]);
  view = newCamera(20,60,user);

  generateDungeon(49,49,400);
  inscribeEntity(user);

  int input;
  do{
    handleInput(input, user);
    drawMap();
  }while((input = getch()) != '/');

  endwin();
}
void init(){
  initscr();
  start_color();
  initColors();
  raw();
  noecho();
  curs_set(0);
  srand((unsigned)time(NULL));
}
int range(int from, int to){
  return rand() % (to-from+1) + from;
}
