#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>

#include "tower.hpp"
#include "entity.hpp"
#include "path.hpp"

class Map
{

public:
   Map();
   void setSize(int x, int y);
   const int* getSize();
   bool addTower(Tower* t);
   bool addEntity(Entity* e);
   bool addPath(Path* p);
   Tower* getTower(int i);
   Entity* getEntity(int i);
   Path* getPath(int i);
   int getNumTowers();
   int getNumEntities();
   int getNumPaths();
   Entity* getClosestEntity(int x, int y);
   bool setStartPoint(int x, int y);
   Path* getStartPoint();
   bool setGoalPoint(int x, int y);
   Path* getGoalPoint();
   Path* bestAdjacentPath(Object* o);
   void moveEntity(Entity* e);
   std::string print();
   ~Map();

private:
   std::vector<Tower*> towers;
   std::vector<Entity*> entities;
   std::vector<Path*> paths;
   int size[2];
   Path startPoint;
   Path goalPoint;
};

#endif // MAP_HPP
