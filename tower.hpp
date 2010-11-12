#ifndef TOWER_HPP
#define TOWER_HPP

#include "object.hpp"
#include "entity.hpp"

class Tower: public Object
{

public:
   Tower();
   Entity* getTarget();
   void setTarget(Entity* e);
   bool isTargetInRange();
   void fireAtTarget();
   ~Tower();

private:
   Entity* target;
   int range;
   int damage;
};

#endif // TOWER_HPP
