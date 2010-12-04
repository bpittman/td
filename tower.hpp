#ifndef TOWER_HPP
#define TOWER_HPP

#include "object.hpp"
#include "entity.hpp"

enum TowerType { TOWER, SLOW_TOWER, LONG_TOWER, SHORT_TOWER };

class Tower: public Object
{

public:
   Tower();
   Entity* getTarget();
   void setTarget(Entity* e);
   bool isTargetAlive();
   bool isTargetInRange();
   void fireAtTarget();
   TowerType getType();
   int getRange();
   int getDamage();
   ~Tower();

protected:
   Entity* target;
   int range;
   int damage;
   TowerType type;
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
