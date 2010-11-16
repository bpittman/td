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
   ~Sim();

private:
   Map* map;
};

#endif // SIM_HPP
