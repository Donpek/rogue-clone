#include "rogue.h"

void main(){
  init();
  tiles = initTiles();
  user = newEntity(50,50,PLAYER_ID);
  currMap = newMap(100,100,tiles[GRASS_ID]);
  view = newCamera(20,60,user);

  currMap->rooms = generateDungeon(49,49,600);
  inscribeEntity(user, currMap->rooms[0]);
  
  int input;
  do{
    handleInput(input);
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
int within(int x, int from, int to){
  if(from >= x && x <= to) return 1;
  else return 0;
}
