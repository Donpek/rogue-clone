#include "rogue.h"

void main(){
  init();
  tiles = initTiles();
  user = newEntity(50,50,PLAYER_ID);
  currMap = newMap(100,100,tiles[GRASS_ID]);
  view = newCamera(20,60,user);

  currMap->rooms = generateDungeon(49,49,120);
  inscribeEntity(user, currMap->rooms[0]);

  int input;
  do{
    handleInput(input);
    drawMap();
    drawUI();
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
void drawUI(){
  int i;
  int h=view->h+1, w=view->w+1;
  attron(COLOR_PAIR(RED));
  mvprintw(0,0,"/");
  mvprintw(0,w,"\\");
  mvprintw(h,0,"\\");
  mvprintw(h,w,"/");
  for(i=1; i<h; i++){
    mvprintw(i,0,"|");
    mvprintw(i,w,"|");
  }
  for(i=1; i<w; i++){
    mvprintw(0,i,"-");
    mvprintw(h,i,"-");
  }

  mvprintw(0,w+1,"/");
  mvprintw(0,w+15,"\\");
  mvprintw(h,w+1,"\\");
  mvprintw(h,w+15,"/");
  for(i=1; i<h; i++){
    mvprintw(i,w+1,"|");
    mvprintw(i,w+15,"|");
  }
  for(i=1; i<14; i++){
    mvprintw(0,w+1+i,"-");
    mvprintw(h,w+1+i,"-");
  }
  attroff(COLOR_PAIR(RED));
}
