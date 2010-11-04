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

Object::~Object()
{

}
