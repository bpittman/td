#include "tower.hpp"

Tower::Tower()
{
   target = 0;
   range = 5;
   damage = 10;
}

void Tower::setTarget(Entity* e)
{
   if(distance(e)<=range && e->alive()) {
      target = e;
   }
   else {
      target = 0;
   }
}

bool Tower::isTargetAlive()
{
   if(target==0) return false;
   return target->alive();
}

bool Tower::isTargetInRange()
{
   if(target==0) return false;
   if(distance(target)<=range) return true;
}

Entity* Tower::getTarget()
{
   return target;
}

void Tower::fireAtTarget()
{
   if(target!=0 && isTargetInRange()) {
      target->setHealth(target->getHealth()-damage);
   }
}

Tower::~Tower()
{

}

SlowTower::SlowTower()
{
   range = 5;
   damage = 0;
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
