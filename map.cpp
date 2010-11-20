#include "map.hpp"

Map::Map()
{
   size[0] = size[1] = 10;
   startPoint.setPosition(0,0);
   goalPoint.setPosition(9,9);
   addPath(&startPoint);
   addPath(&goalPoint);
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

//towers cannot overlap with each other, or be on a path
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
   for(int i=0;i<paths.size();++i) {
      if(paths[i]->getPosition()[0] == t->getPosition()[0] &&
         paths[i]->getPosition()[1] == t->getPosition()[1]) {
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
   for(int i=0;i<paths.size();++i) {
      if(paths[i]->getPosition()[0] == e->getPosition()[0] &&
         paths[i]->getPosition()[1] == e->getPosition()[1]) {
         entities.push_back(e);
         return true;
      }
   }
   return false;
}

//paths cannot overlap with each other, or towers
bool Map::addPath(Path* p)
{
   if(p->getPosition()[0] >= size[0] ||
      p->getPosition()[1] >= size[1]) return false;

   for(int i=0;i<towers.size();++i) {
      if(towers[i]->getPosition()[0] == p->getPosition()[0] &&
         towers[i]->getPosition()[1] == p->getPosition()[1]) {
	 return false;
      }
   }
   for(int i=0;i<paths.size();++i) {
      if(paths[i]->getPosition()[0] == p->getPosition()[0] &&
         paths[i]->getPosition()[1] == p->getPosition()[1]) {
	 return false;
      }
   }
   paths.push_back(p);
   return true;
}

Tower* Map::getTower(int i)
{
   if(i<towers.size()) return towers[i];
   else                return NULL;
}

Entity* Map::getEntity(int i)
{
   if(i<entities.size()) return entities[i];
   else                  return NULL;
}

Path* Map::getPath(int i)
{
   if(i<paths.size()) return paths[i];
   else               return NULL;
}

int Map::getNumTowers()
{
   return towers.size();
}

int Map::getNumEntities()
{
   return entities.size();
}

int Map::getNumPaths()
{
   return paths.size();
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

Path* Map::getStartPoint()
{
   return &startPoint;
}

bool Map::setGoalPoint(int x, int y)
{
   if(x >= size[0] || y >= size[1]) return false;
   goalPoint.setPosition(x,y);
   return true;
}

Path* Map::getGoalPoint()
{
   return &goalPoint;
}

Path* Map::bestAdjacentPath(Path* p)
{
   double best,d;
   Path* bestPath = NULL;
   best = -1;
   for(int i=0;i<paths.size();++i) {
      if(paths[i]->adjacent(p)) {
         d = goalPoint.distance(paths[i]);
	 if(best < 0 || d < best) {
	    best = d;
	    bestPath = paths[i];
	 }
      }
   }
   return bestPath;
}

Map::~Map()
{

}
