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
   ~Tower();

private:
   Entity* target;
   int range;
};

#endif // TOWER_HPP
