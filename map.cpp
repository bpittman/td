#include "map.hpp"

Map::Map()
{

}

void Map::addTower(Tower* t)
{
   towers.push_back(t);
}

void Map::addEntity(Entity* e)
{
   entities.push_back(e);
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
