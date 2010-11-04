#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "object.hpp"

class Map
{

public:
   Map();
   void addObject(Object* o);
   Object* getObject(int i);
   ~Map();

private:
   std::vector<Object*> objects;
};

#endif // MAP_HPP
