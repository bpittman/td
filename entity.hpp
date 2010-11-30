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
   bool getSlowed();
   void setSlowed(bool s);
   void setPosition(int x, int y);
   ~Entity();

private:
   int health;
   bool slowed;
};

#endif // ENTITY_HPP
