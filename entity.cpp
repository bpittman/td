#include "entity.hpp"

Entity::Entity()
{
   health = 100;
}

int Entity::getHealth()
{
   return health;
}

void Entity::setHealth(int h)
{
   health = h;
}

bool Entity::alive()
{
   return health > 0;
}

bool Entity::getSlowed()
{
   return slowed;
}

void Entity::setSlowed(bool s)
{
   slowed = s;
}

Entity::~Entity()
{

}
