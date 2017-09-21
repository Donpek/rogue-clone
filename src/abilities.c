#include "rogue.h"

void punch(Entity* user, Entity* target){
  int dmg;
  if(user->stamina >= 2){
    dmg = user->stamina / 8;
    // eventLog = "* %s punches %s dealing %d damage.",
    //   user->name, target->name, dmg;
    target->hp -= dmg;
    user->stamina -= 2;
    if(target->hp <= 0){
      eraseEntity(target);
    }
  }else{
    // eventLog = "* %s tried to punch, but was too tired.",
    //   user->name;
  }
}

void bodySlam(Entity* user, Entity* target){
  int dmg;
  if(user->stamina >= 2){
    dmg = user->weight / 2;
    // eventLog = "* %s body slams %s dealing %d damage.",
    //   user->name, target->name, dmg;
    target->hp -= dmg;
    user->stamina -= user->weight / 8;
    if(target->hp <= 0){
      eraseEntity(target);
    }
  }else{
    // eventLog = "* %s tried to body slam, but was too tired.",
    //   user->name;
  }
}
