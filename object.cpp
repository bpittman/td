#include <math.h>
#include <stdlib.h>

#include "object.hpp"

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

bool Object::adjacent(Object* o)
{
   return (o!=this &&
           abs(position[0] - o->getPosition()[0])<=1 &&
           abs(position[1] - o->getPosition()[1])<=1);
}

Object::~Object()
{

}
