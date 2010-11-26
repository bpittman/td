#include <stdlib.h>

#include "sim.hpp"

Sim::Sim()
{
   map = new Map();
   srand(1);
   numTowers = 5;
   numEntities = 10;
}

void Sim::tick()
{
   for(int i=0;i<map->getNumEntities();++i) {
      map->moveEntity(map->getEntity(i));
   }
   spawn();
}

Map* Sim::getMap()
{
   return map;
}

bool Sim::populateMap()
{
   int x = map->getSize()[0];
   int y = map->getSize()[1];
   int xx,yy;
   if(x*y<numTowers) return false; //FIXME: this should count empty squares
   while(map->getNumTowers()<numTowers) {
      xx = rand() % x;
      yy = rand() % y;
      Tower *t = new Tower;
      t->setPosition(xx,yy);
      if(!map->addTower(t)) delete t;
   }
   return true;
}

bool Sim::spawn()
{
   if(map->getNumEntities() < numEntities) {
      Entity* e = new Entity();
      e->setPosition(map->getStartPoint()->getPosition()[0],
                     map->getStartPoint()->getPosition()[1]);
      map->addEntity(e);
      return true;
   }
   return false;
}

int Sim::entitiesAtGoal()
{
   int entitiesAtGoal = 0;
   int x = map->getGoalPoint()->getPosition()[0];
   int y = map->getGoalPoint()->getPosition()[1];
   for(int i=0;i<map->getNumEntities();++i) {
      if(map->getEntity(i)->getPosition()[0] == x &&
         map->getEntity(i)->getPosition()[1] == y) {
	 entitiesAtGoal++;
      }
   }
   return entitiesAtGoal;
}

Sim::~Sim()
{
   for(int i=0;i<map->getNumTowers();++i) {
      delete map->getTower(i);
   }
   for(int i=0;i<map->getNumEntities();++i) {
      delete map->getEntity(i);
   }
   for(int i=0;i<map->getNumPaths();++i) {
      if(map->getPath(i)==map->getStartPoint()) continue;
      if(map->getPath(i)==map->getGoalPoint()) continue;
      delete map->getPath(i);
   }
   delete map;
}
