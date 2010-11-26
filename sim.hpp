#ifndef SIM_HPP
#define SIM_HPP

#include "object.hpp"
#include "entity.hpp"
#include "map.hpp"

class Sim
{

public:
   Sim();
   void tick();
   Map* getMap();
   bool populateMap();
   bool spawn();
   int entitiesAtGoal();
   ~Sim();

private:
   Map* map;
   int numTowers;
   int numEntities;
};

#endif // SIM_HPP
