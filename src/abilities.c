#include "rogue.h"

void punch(Entity* user, Entity* target){
  int dmg;
  char* dmgS = malloc(sizeof(char)*4);
  char* msg = malloc(sizeof(char)*view->w);
  strcat(msg, "* ");

  if(user->stamina >= 2){
    dmg = user->stamina / 8;
    target->hp -= dmg;
    user->stamina -= 2;

    if(target->hp <= 0){
      strcat(msg, target->name);
      strcat(msg, " has been punched to death.");
      log(msg);
      eraseEntity(target);
      return;
    }
    sprintf(dmgS, "%d", dmg);
    strcat(msg, user->name);
    strcat(msg, " punches ");
    strcat(msg, target->name);
    strcat(msg, " dealing ");
    strcat(msg, dmgS);
    strcat(msg, " damage.");
    log(msg);
  }else{
    strcat(msg, user->name);
    strcat(msg, " tried to do a punch, but was too tired.");
    log(msg);
  }
}

void bodySlam(Entity* user, Entity* target){
  int dmg;
  char* dmgS = malloc(sizeof(char)*4);
  char* msg = malloc(sizeof(char)*view->w);
  strcat(msg, "* ");
  if(user->stamina >= 2){
    dmg = user->weight / 2;
    target->hp -= dmg;
    user->stamina -= user->weight / 8;

    if(target->hp <= 0){
      strcat(msg, target->name);
      strcat(msg, " has been crushed to death by ");
      strcat(msg, user->name);
      strcat(msg, ".");
      log(msg);
      eraseEntity(target);
      return;
    }
    strcat(msg, user->name);
    strcat(msg, " body slams ");
    strcat(msg, target->name);
    strcat(msg, " dealing "); sprintf(dmgS,"%d",dmg);
    strcat(msg, dmgS);
    strcat(msg, " damage.");
    log(msg);
  }else{
    strcat(msg, user->name);
    strcat(msg, " tried body slamming ");
    strcat(msg, target->name);
    strcat(msg, ", but was too tired.");
    log(msg);
  }
}
