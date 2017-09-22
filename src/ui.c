#include "rogue.h"

void setLog(char* text, int lineIndex){
  int i,j;

  for(i=0;i<view->w;i++){
    if(text[i] != '\0'){
      eventLog[lineIndex][i] = text[i];}
    else{
      for(j=i; j<view->w; j++){
        eventLog[lineIndex][j] = ' ';}
      return;
    }
  }
}
void log(char* message){
  setLog(eventLog[1],0);
  setLog(eventLog[2],1);
  setLog(message,2);
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
  mvprintw(h+4,0,"\\");
  mvprintw(h+4,w,"/");
  mvprintw(h+1,0,"|");
  mvprintw(h+2,0,"|");
  mvprintw(h+3,0,"|");
  mvprintw(h+1,w,"|");
  mvprintw(h+2,w,"|");
  mvprintw(h+3,w,"|");
  for(i=1; i<w; i++){
    mvprintw(h+4,i,"-");
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
  mvprintw(ly+1,lx+1,"==============");
  mvprintw(ly+2,lx+1," rogue-clone");
  mvprintw(ly+3,lx+1,"==============");

  mvprintw(ly+5,lx+1,"====Health====");

  mvprintw(ly+7,lx+1,"===Stamina====");

  mvprintw(ly+9,lx+1,"====Weight====");

  mvprintw(ly+11,lx+1,"==============");

  mvprintw(ly+13,lx+1,"====Floor=====");
  mvprintw(ly+14,lx+1," TO-DO");
  mvprintw(ly+15,lx+1,"==============");
  /**/

  attroff(COLOR_PAIR(RED));

  /*log content*/
  mvprintw(view->h+2,1,eventLog[0]);
  mvprintw(view->h+3,1,eventLog[1]);
  mvprintw(view->h+4,1,eventLog[2]);
  /**/

  /*stats content*/
  mvprintw(ly+6,lx+1," %d (%d)",
    player->hp, player->maxhp);
  mvprintw(ly+8,lx+1," %d (%d)",
    player->stamina, player->maxStamina);
  mvprintw(ly+10,lx+1," %d (%d)",
    player->weight, player->maxWeight);
  /**/
}
