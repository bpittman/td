#include "object.hpp"

#include <math.h>

Object::Object()
{
   position[0] = position[1] = 0;
}

void Object::setPosition(int x, int y)
{
   position[0] = x;
   position[1] = y;
}

const int* Object::getPosition()
{
   return position;
}

double Object::distance(Object* o)
{
   return sqrt(pow(o->getPosition()[0]-position[0],2) +
               pow(o->getPosition()[1]-position[1],2));
}

Object::~Object()
{

}
