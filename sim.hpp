#ifndef SIM_HPP
#define SIM_HPP

#include "object.hpp"
#include "entity.hpp"
#include "map.hpp"

class Sim
{

public:
   Sim();
   Map* getMap();
   bool populateMap();
   ~Sim();

private:
   Map* map;
   int numTowers;
};

#endif // SIM_HPP
