#include <gtest/gtest.h>

#include "tower.hpp"
#include "entity.hpp"
#include "map.hpp"

TEST(Tower, CreateTower) {
  Tower* t = NULL;
  t = new Tower();
  ASSERT_TRUE(t != NULL);
  delete t;
}

TEST(Tower, SetPosition) {
  Tower* t = NULL;
  t = new Tower();
  t->setPosition(1,2);
  EXPECT_EQ(1,t->getPosition()[0]);
  EXPECT_EQ(2,t->getPosition()[1]);
  delete t;
}

TEST(Entity, CreateEntity) {
  Entity* e = NULL;
  e = new Entity();
  ASSERT_TRUE(e != NULL);
  delete e;
}

TEST(Entity, SetPosition) {
  Entity* e = NULL;
  e = new Entity();
  e->setPosition(1,2);
  EXPECT_EQ(1,e->getPosition()[0]);
  EXPECT_EQ(2,e->getPosition()[1]);
  delete e;
}

TEST(Map, createMap) {
  Map* m = NULL;
  m = new Map();
  ASSERT_TRUE(m != NULL);
  delete m;
}

TEST(Map, addTower) {
  Map* m = NULL;
  m = new Map();

  Tower* t = NULL;
  t = new Tower();

  m->addTower(t);
  ASSERT_EQ(t,m->getTower(0));
  delete m;
  delete t;
}

TEST(Map, addEntity) {
  Map* m = NULL;
  m = new Map();

  Entity* e = NULL;
  e = new Entity();

  m->addEntity(e);
  ASSERT_EQ(e,m->getEntity(0));
  delete m;
  delete e;
}

TEST(Map, objectOutOfRange) {
  Map* m = NULL;
  m = new Map();

  ASSERT_EQ(NULL,m->getTower(0));
  ASSERT_EQ(NULL,m->getEntity(0));
  delete m;
}
