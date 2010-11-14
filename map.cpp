#include "map.hpp"

Map::Map()
{
   size[0] = size[1] = 10;
}

void Map::setSize(int x, int y)
{
   size[0] = x;
   size[1] = y;
}

const int* Map::getSize()
{
   return size;
}

bool Map::addTower(Tower* t)
{
   if(t->getPosition()[0] >= size[0] ||
      t->getPosition()[1] >= size[1]) return false;

   for(int i=0;i<towers.size();++i) {
      if(towers[i]->getPosition()[0] == t->getPosition()[0] &&
         towers[i]->getPosition()[1] == t->getPosition()[1]) {
	 return false;
      }
   }
   towers.push_back(t);
   return true;
}

//entities can overlap with each other, but not with towers
bool Map::addEntity(Entity* e)
{
   if(e->getPosition()[0] >= size[0] ||
      e->getPosition()[1] >= size[1]) return false;

   for(int i=0;i<towers.size();++i) {
      if(towers[i]->getPosition()[0] == e->getPosition()[0] &&
         towers[i]->getPosition()[1] == e->getPosition()[1]) {
	 return false;
      }
   }
   entities.push_back(e);
   return true;
}

Tower* Map::getTower(int i)
{
   if(i<towers.size()) return towers[i];
   else                 return NULL;
}

Entity* Map::getEntity(int i)
{
   if(i<entities.size()) return entities[i];
   else                 return NULL;
}

Entity* Map::getClosestEntity(int x, int y)
{
   Object o;
   o.setPosition(x,y);
   Entity* closest = NULL;
   double minDist = -1, dist;
   for(int i=0; i<entities.size(); ++i) {
      dist = o.distance(entities[i]);
      if(minDist < 0 || dist < minDist) {
         closest = entities[i];
	 minDist = dist;
      }
   }
   return closest;
}

bool Map::setStartPoint(int x, int y)
{
   if(x >= size[0] || y >= size[1]) return false;
   startPoint.setPosition(x,y);
   return true;
}

const int* Map::getStartPoint()
{
   return startPoint.getPosition();
}

bool Map::setGoalPoint(int x, int y)
{
   if(x >= size[0] || y >= size[1]) return false;
   goalPoint.setPosition(x,y);
   return true;
}

const int* Map::getGoalPoint()
{
   return goalPoint.getPosition();
}

Map::~Map()
{

}
