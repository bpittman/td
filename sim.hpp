#ifndef SIM_HPP
#define SIM_HPP

#include "object.hpp"
#include "entity.hpp"
#include "map.hpp"

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

class Sim
{

public:
   Sim();
   void tick();
   Map* getMap();
   bool populateMap();
   bool spawn();
   int entitiesAtGoal();
   int activeEntities();
   int* getTowerList();
   void setTowersFromList(int* tlist, int num);
   void mutateTower();
   void crossoverTowers(Sim* s1, Sim* s2);
   ~Sim();

private:
   Map* map;
   int numTowers;
   int numEntities;
};

#endif // SIM_HPP
