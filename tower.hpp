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
   ~Tower();

private:
   Entity* target;
};

#endif // TOWER_HPP
