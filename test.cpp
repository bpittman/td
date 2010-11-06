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

TEST(Map, addTowerOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t1 = new Tower();
  Tower* t2 = new Tower();

  EXPECT_TRUE(m->addTower(t1));
  EXPECT_FALSE(m->addTower(t2));

  delete m;
  delete t1, t2;
}

TEST(Map, addTowerNonOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t1 = new Tower();
  Tower* t2 = new Tower();
  t2->setPosition(0,1);

  EXPECT_TRUE(m->addTower(t1));
  EXPECT_TRUE(m->addTower(t2));

  delete m;
  delete t1, t2;
}

TEST(Map, addEntityOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t = new Tower();
  Entity* e = new Entity();

  EXPECT_TRUE(m->addTower(t));
  EXPECT_FALSE(m->addEntity(e));

  delete m;
  delete t, e;
}

TEST(Map, addEntityNonOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t = new Tower();
  Entity* e1 = new Entity();
  Entity* e2 = new Entity();
  e1->setPosition(0,1);
  e2->setPosition(0,1);

  EXPECT_TRUE(m->addTower(t));
  EXPECT_TRUE(m->addEntity(e1));
  EXPECT_TRUE(m->addEntity(e2));

  delete m;
  delete t, e1, e2;
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

TEST(Map, setSize) {
  Map* m = new Map();
  m->setSize(10,20);

  EXPECT_EQ(10,m->getSize()[0]);
  EXPECT_EQ(20,m->getSize()[1]);
  delete m;
}

TEST(Map, positionOutOfRange) {
  Map* m = new Map();
  m->setSize(10,20);

  Entity* e = new Entity();

  e->setPosition(10,0);
  EXPECT_FALSE(m->addEntity(e));

  e->setPosition(0,20);
  EXPECT_FALSE(m->addEntity(e));

  e->setPosition(0,0);
  EXPECT_TRUE(m->addEntity(e));
  delete m;
}
