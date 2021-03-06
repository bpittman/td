#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "sim.hpp"

Sim::Sim()
{
   map = new Map();
   numTowers = 5;
   numEntities = 10;
   spawnPerTick = 1;
   overrideEntities = -1;
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
   int i=0;
   while(map->getNumTowers()<numTowers) {
      xx = rand() % x;
      yy = rand() % y;
      Tower *t;
      if(i<2) t = new SlowTower;
      else if(i%2) t = new ShortTower;
      else t = new LongTower;
      t->setPosition(xx,yy);
      if(!map->addTower(t)) delete t;
      else i++;
   }
   return true;
}

bool Sim::spawn()
{
   for(int i=0;i<spawnPerTick;++i) {
      if(map->getNumEntities() < numEntities) {
         Entity* e = new Entity();
         e->setPosition(map->getStartPoint()->getPosition()[0],
                        map->getStartPoint()->getPosition()[1]);
         map->addEntity(e);
      }
      else {
         return false;
      }
   }
   return true;
}

void Sim::overrideEntitiesAtGoal(int e)
{
   overrideEntities = e;
}

int Sim::entitiesAtGoal()
{
   if(overrideEntities >=0) return overrideEntities;

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
   activeEntities += numEntities - map->getNumEntities();
   return activeEntities;
}

std::string Sim::getTowerListString()
{
   std::stringstream t;
   int *tlist = NULL;
   if(map->getNumTowers()) {
      tlist = new int[map->getNumTowers()*3];
      for(int i=0;i<map->getNumTowers();++i) {
	 tlist[i*3] = map->getTower(i)->getPosition()[0];
	 tlist[i*3+1] = map->getTower(i)->getPosition()[1];
	 tlist[i*3+2] = map->getTower(i)->getType();
	 t << map->getTower(i)->getPosition()[0] << ' '
	   << map->getTower(i)->getPosition()[1] << ' '
	   << map->getTower(i)->getType();
	 if(i<map->getNumTowers()-1) t << ' ';
      }
   }
   return t.str();
}

int* Sim::getTowerList()
{
   int *tlist = NULL;
   if(map->getNumTowers()) {
      tlist = new int[map->getNumTowers()*3];
      for(int i=0;i<map->getNumTowers();++i) {
	 tlist[i*3] = map->getTower(i)->getPosition()[0];
	 tlist[i*3+1] = map->getTower(i)->getPosition()[1];
	 tlist[i*3+2] = map->getTower(i)->getType();
      }
   }
   return tlist;
}

void Sim::setTowersFromList(int* tlist, int num)
{
   for(int i=0;i<num/3;++i) {
      Tower *t;
      if(tlist[i*3+2] == TOWER) t = new Tower;
      else if(tlist[i*3+2] == SLOW_TOWER) t = new SlowTower;
      else if(tlist[i*3+2] == LONG_TOWER) t = new LongTower;
      else if(tlist[i*3+2] == SHORT_TOWER) t = new ShortTower;

      t->setPosition(tlist[i*3],tlist[i*3+1]);
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
      TowerType type = s1->getMap()->getTower(i)->getType();
      Tower* t;
      if(type==TOWER) t = new Tower();
      else if(type==SLOW_TOWER) t = new SlowTower();
      else if(type==LONG_TOWER) t = new LongTower();
      else if(type==SHORT_TOWER) t = new ShortTower();
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


void Sim::setSpawnPerTick(int s)
{
   spawnPerTick = s;
}

int Sim::getSpawnPerTick()
{
   return spawnPerTick;
}

void Sim::encodeForMPI(int* a)
{
   for(int i=0;i<map->getNumTowers();++i) {
      a[i*3]   = map->getTower(i)->getPosition()[0];
      a[i*3+1] = map->getTower(i)->getPosition()[1];
      a[i*3+2] = map->getTower(i)->getType();
   }
   a[map->getNumTowers()*3] = entitiesAtGoal();
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

BigSim::BigSim()
{
   numTowers = 15;
   numEntities = 100;
   spawnPerTick = 2;
   map = new Map();
   map->setSize(50,50);
   map->setStartPoint(0,0);
   map->setGoalPoint(49,49);
   for(int i=1;i<map->getSize()[0]-1;++i) {
      Path* p = new Path();
      p->setPosition(i,i);
      map->addPath(p);
   }
}

BigSim::~BigSim()
{

}
