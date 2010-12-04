#include <stdlib.h>

#include "tower.hpp"

Tower::Tower()
{
   target = NULL;
   range = 5;
   damage = 10;
}

void Tower::setTarget(Entity* e)
{
   if(distance(e)<=range && e->alive()) {
      target = e;
   }
   else {
      target = NULL;
   }
}

bool Tower::isTargetAlive()
{
   if(target==NULL) return false;
   return target->alive();
}

bool Tower::isTargetInRange()
{
   if(target==NULL) return false;
   return distance(target)<=range;
}

Entity* Tower::getTarget()
{
   return target;
}

void Tower::fireAtTarget()
{
   if(target!=NULL && isTargetInRange()) {
      target->setHealth(target->getHealth()-damage);
   }
}

int Tower::getRange()
{
   return range;
}

int Tower::getDamage()
{
   return damage;
}

Tower::~Tower()
{

}

SlowTower::SlowTower()
{
   range = 5;
   damage = 0;
}

void SlowTower::fireAtTarget()
{
   if(target!=0 && isTargetInRange()) {
      target->setSlowed(true);
   }
}

SlowTower::~SlowTower()
{

}

LongTower::LongTower()
{
   range = 10;
   damage = 5;
}

LongTower::~LongTower()
{

}

ShortTower::ShortTower()
{
   range = 3;
   damage = 20;
}

ShortTower::~ShortTower()
{

}
