#include "rogue.h"

void main(){
  init();
  Tile* tiles = initTiles();
  Entity * user = newEntity(50,50,tiles[PLAYER_ID]);
  Map * test = newMap(100,100,tiles[GRASS_ID]);
  Camera * view = newCamera(20,60,user);

  generateDungeon(test,49,49,400,tiles);
  inscribeEntity(user,test);

  int input;
  do{
    handleInput(input, user, test);
    drawMap(test, view);
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
