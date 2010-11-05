#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "tower.hpp"
#include "entity.hpp"

class Map
{

public:
   Map();
   void addTower(Tower* t);
   void addEntity(Entity* e);
   Tower* getTower(int i);
   Entity* getEntity(int i);
   ~Map();

private:
   std::vector<Tower*> towers;
   std::vector<Entity*> entities;
};

#endif // MAP_HPP
