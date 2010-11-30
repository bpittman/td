#include <stdlib.h>

#include "sim.hpp"

Sim::Sim()
{
   map = new Map();
   numTowers = 5;
   numEntities = 10;
}

void Sim::tick()
{
   //move entities
   for(int i=0;i<map->getNumEntities();++i) {
      map->moveEntity(map->getEntity(i));
   }

   //spawn new entities
   spawn();

   //find targets and fire
   for(int i=0;i<map->getNumTowers();++i) {
      Tower *t = map->getTower(i);
      if(!(t->isTargetAlive() && t->isTargetInRange())) {
         t->setTarget(map->getClosestEntity(t->getPosition()[0],t->getPosition()[1]));
      }
      t->fireAtTarget();
   }
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

int Sim::activeEntities()
{
   int activeEntities = 0;
   int x = map->getGoalPoint()->getPosition()[0];
   int y = map->getGoalPoint()->getPosition()[1];
   for(int i=0;i<map->getNumEntities();++i) {
      if(!(map->getEntity(i)->getPosition()[0] == x &&
           map->getEntity(i)->getPosition()[1] == y) &&
	   map->getEntity(i)->alive()) {
	 activeEntities++;
      }
   }
   return activeEntities;
}

int* Sim::getTowerList()
{
   int *tlist = NULL;
   if(map->getNumTowers()) {
      tlist = new int[map->getNumTowers()*2];
      for(int i=0;i<map->getNumTowers();++i) {
	 tlist[i*2] = map->getTower(i)->getPosition()[0];
	 tlist[i*2+1] = map->getTower(i)->getPosition()[1];
      }
   }
   return tlist;
}

void Sim::setTowersFromList(int* tlist, int num)
{
   for(int i=0;i<num/2;++i) {
      Tower *t = new Tower;
      t->setPosition(tlist[i*2],tlist[i*2+1]);
      if(!map->addTower(t)) delete t;
   }
}

void Sim::mutateTower()
{
   if(map->getNumTowers() == 0) return;
   int i = rand() % map->getNumTowers();
   int x = rand() % map->getSize()[0];
   int y = rand() % map->getSize()[1];

   while(!map->checkTowerPos(x,y)) {
      x = rand() % map->getSize()[0];
      y = rand() % map->getSize()[1];
   }
   map->getTower(i)->setPosition(x,y);
}

void Sim::crossoverTowers(Sim* s1, Sim* s2)
{
   if(s1==NULL || s2==NULL) return;
   int x1,y1, x2,y2;
   int minTowers = min(s1->getMap()->getNumTowers(),s2->getMap()->getNumTowers());
   for(int i=0;i<minTowers;++i) {
      x1 = s1->getMap()->getTower(i)->getPosition()[0];
      y1 = s1->getMap()->getTower(i)->getPosition()[1];
      x2 = s2->getMap()->getTower(i)->getPosition()[0];
      y2 = s2->getMap()->getTower(i)->getPosition()[1];
      Tower* t = new Tower();
      //try to grab a tower position from sim1 or sim2
      if((rand()%2==0) && map->checkTowerPos(x1,y1)) {
         t->setPosition(x1,y1);
	 map->addTower(t);
      }
      else if(map->checkTowerPos(x2,y2)) {
         t->setPosition(x2,y2);
	 map->addTower(t);
      }
      //if both those positions are taken, punt and place it randomly
      else {
	 x1 = rand() % map->getSize()[0];
	 y1 = rand() % map->getSize()[1];
	 while(!map->checkTowerPos(x1,y1)) {
	    x1 = rand() % map->getSize()[0];
	    y1 = rand() % map->getSize()[1];
	 }
	 t->setPosition(x1,y1);
	 map->addTower(t);
      }
   }
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
