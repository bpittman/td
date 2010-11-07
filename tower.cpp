#include "tower.hpp"

Tower::Tower()
{
   target = 0;
}

void Tower::setTarget(Entity* e)
{
   target = e;
}

Entity* Tower::getTarget()
{
   return target;
}

Tower::~Tower()
{

}
