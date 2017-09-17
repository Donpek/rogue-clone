#include "rogue.h"

void punch(Entity* user, Entity* target){
  if(user->stamina >= 2){
    target->hp -= user->stamina / 4;
    user->stamina /= 2;
    if(target->hp <= 0){
      eraseEntity(target);
    }
  }
}

void bodySlam(Entity* user, Entity* target){
  if(user->stamina >= 2){
    target->hp -= user->weight / 2;
    user->stamina -= user->weight / 4;
    if(target->hp <= 0){
      eraseEntity(target);
    }
  }
}
