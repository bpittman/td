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
   bool isTargetAlive();
   bool isTargetInRange();
   void fireAtTarget();
   ~Tower();

protected:
   Entity* target;
   int range;
   int damage;
};

class SlowTower: public Tower
{

public:
   SlowTower();
   void fireAtTarget();
   ~SlowTower();

};

class LongTower: public Tower
{

public:
   LongTower();
   ~LongTower();

};

class ShortTower: public Tower
{

public:
   ShortTower();
   ~ShortTower();

};

#endif // TOWER_HPP
