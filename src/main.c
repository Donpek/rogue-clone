#include "rogue.h"

int main(){
  init();
  log("* You find yourself inside of a dungeon.");

  int input;
  do{
    updateStats();
    handleInput(input);
    drawMap();
    drawUI();
  }while((input = getch()) != '/' && !gameOver);

  endwin();
  printf("==============GAME=OVER==============\n");
  return 0;
}
int range(int from, int to){
  return rand() % (to-from+1) + from;
}
int within(int x, int from, int to){
  if(from >= x && x <= to) return 1;
  else return 0;
}
