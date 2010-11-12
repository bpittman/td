#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "tower.hpp"
#include "entity.hpp"

class Map
{

public:
   Map();
   void setSize(int x, int y);
   const int* getSize();
   bool addTower(Tower* t);
   bool addEntity(Entity* e);
   Tower* getTower(int i);
   Entity* getEntity(int i);
   Entity* getClosestEntity(int x, int y);
   bool setStartPoint(int x, int y);
   const int* getStartPoint();
   bool setGoalPoint(int x, int y);
   const int* getGoalPoint();
   ~Map();

private:
   std::vector<Tower*> towers;
   std::vector<Entity*> entities;
   int size[2];
   int startPoint[2];
   int goalPoint[2];
};

#endif // MAP_HPP
