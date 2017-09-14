#include "rogue.h"

void main(){
  init();

  Entity * user = newEntity(2,2,PLAYER);
  Map * test = newMap(100,100,GRASS);
  Camera * view = newCamera(20,60,user);

  generateDungeon(test,1,1,20);
  inscribeEntity(user,test);



  int input;
  do{
    handleInput(input, user, test);
    drawMap(test, view);
  }while((input = getch()) != 'q');

  endwin();
}
void init(){
  initscr();
  raw();
  noecho();
  curs_set(0);
  srand(time(NULL));
}
