#include "rogue.h"

void main(){
  init();
  tiles = initTiles();
  user = newEntity(100,100,PLAYER_ID);
  currMap = newMap(200,200,tiles[GRASS_ID]);
  view = newCamera(20,60,user);
  userName = "Anpuk";
  eventLog = "* You find yourself in an underground dungeon.";

  currMap->rooms = generateDungeon(99,99,600);
  inscribeEntity(user, currMap->rooms[0]);

  int input;
  do{
    handleInput(input);
    drawMap();
    drawUI();
    mvprintw(view->h+2,1,eventLog);
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
  /*view*/
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
  /**/

  /*log*/
  mvprintw(h+2,0,"\\");
  mvprintw(h+2,w,"/");
  mvprintw(h+1,0,"|");
  mvprintw(h+1,w,"|");
  for(i=1; i<w; i++){
    mvprintw(h+2,i,"-");
  }
  /**/

  /*stats*/
  int ly=0,lx=w+1,lh=h,lw=lx+15;
  mvprintw(0,lx,"/");
  mvprintw(0,lw,"\\");
  mvprintw(lh,lx,"\\");
  mvprintw(lh,lw,"/");
  for(i=1; i<h; i++){
    mvprintw(i,lx,"|");
    mvprintw(i,lw,"|");
  }
  for(i=1; i<15; i++){
    mvprintw(0,lx+i,"-");
    mvprintw(lh,lx+i,"-");
  }
  mvprintw(ly+1,lx+1,"=====Name=====");
  mvprintw(ly+2,lx+2,userName);
  mvprintw(ly+3,lx+1,"==============");

  mvprintw(ly+5,lx+1,"====Health====");
  mvprintw(ly+6,lx+1," %d (%d)",
    user->hp, user->maxhp);
  mvprintw(ly+7,lx+1,"===Stamina====");
  mvprintw(ly+8,lx+1," %d (%d)",
    user->stamina, user->maxStamina);
  mvprintw(ly+9,lx+1,"====Weight====");
  mvprintw(ly+10,lx+1," %d (%d)",
    user->weight, user->maxWeight);
  mvprintw(ly+11,lx+1,"==============");

  mvprintw(ly+13,lx+1,"====Floor=====");
  mvprintw(ly+14,lx+1," TO-DO");
  mvprintw(ly+15,lx+1,"==============");
  /**/

  attroff(COLOR_PAIR(RED));
}
