#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "object.hpp"

class Entity: public Object
{

public:
   Entity();
   int getHealth();
   void setHealth(int h);
   bool alive();
   ~Entity();

private:
   int health;
};

#endif // ENTITY_HPP
