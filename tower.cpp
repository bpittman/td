#include "tower.hpp"
#include <math.h>

Tower::Tower()
{
   target = 0;
   range = 5;
}

void Tower::setTarget(Entity* e)
{
   double dist = sqrt(pow(e->getPosition()[0]-position[0],2) +
                      pow(e->getPosition()[1]-position[1],2));
   if(dist<=range) {
      target = e;
   }
}

bool Tower::isTargetInRange()
{
   if(target==0) return false;
   double dist = sqrt(pow(target->getPosition()[0]-position[0],2) +
                      pow(target->getPosition()[1]-position[1],2));
   if(dist<=range) return true;
}

Entity* Tower::getTarget()
{
   return target;
}

Tower::~Tower()
{

}
