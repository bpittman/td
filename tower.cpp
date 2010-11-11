#include "tower.hpp"

Tower::Tower()
{
   target = 0;
   range = 5;
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

Tower::~Tower()
{

}
