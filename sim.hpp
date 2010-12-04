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
   std::string getTowerListString();
   void setTowersFromList(int* tlist, int num);
   void mutateTower();
   void crossoverTowers(Sim* s1, Sim* s2);
   void setSpawnPerTick(int s);
   int getSpawnPerTick();
   ~Sim();

protected:
   Map* map;
   int numTowers;
   int numEntities;
   int spawnPerTick;
};


class BigSim: public Sim
{

public:
   BigSim();
   ~BigSim();

};

#endif // SIM_HPP
