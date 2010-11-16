#include "sim.hpp"

Sim::Sim()
{
   map = new Map();
}

Map* Sim::getMap()
{
   return map;
}

Sim::~Sim()
{
   delete map;
}
