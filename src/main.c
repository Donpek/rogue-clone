#include "rogue.h"

void main(){
  init();

  Entity * user = newEntity(50,50,PLAYER);
  Map * test = newMap(100,100," ");
  Camera * view = newCamera(20,60,user);

  generateDungeon(test,49,49,400);
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
  raw();
  noecho();
  curs_set(0);
  srand((unsigned)time(NULL));
}
