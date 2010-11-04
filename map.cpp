#include "map.hpp"

Map::Map()
{

}

void Map::addObject(Object* o)
{
   objects.push_back(o);
}

Object* Map::getObject(int i)
{
   if(i<objects.size()) return objects[i];
   else                 return NULL;
}

Map::~Map()
{

}
