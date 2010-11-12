#include "tower.hpp"

Tower::Tower()
{
   target = 0;
   range = 5;
   damage = 10;
}

void Tower::setTarget(Entity* e)
{
   if(distance(e)<=range) {
      target = e;
   }
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
