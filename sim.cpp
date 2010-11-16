#include <stdlib.h>

#include "sim.hpp"

Sim::Sim()
{
   map = new Map();
   srand(1);
   numTowers = 5;
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

Sim::~Sim()
{
   for(int i=0;i<map->getNumTowers();++i) {
      delete map->getTower(i);
   }
   delete map;
}
