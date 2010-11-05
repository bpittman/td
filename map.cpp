#include "map.hpp"

Map::Map()
{

}

bool Map::addTower(Tower* t)
{
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

Map::~Map()
{

}
