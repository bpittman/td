#include <gtest/gtest.h>
#include <math.h>

#include "object.hpp"
#include "tower.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "sim.hpp"
#include "path.hpp"

TEST(Object, Distance) {
  Object* o1 = new Object();
  o1->setPosition(0,0);
  Object* o2 = new Object();
  o2->setPosition(0,5);
  EXPECT_DOUBLE_EQ(5.0,o1->distance(o2));
  o2->setPosition(1,1);
  EXPECT_DOUBLE_EQ(sqrt(2),o2->distance(o1));
  o2->setPosition(2,2);
  EXPECT_DOUBLE_EQ(sqrt(8),o2->distance(o1));
  delete o1,o2;
}

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

TEST(Tower, SetTarget) {
  Tower* t = new Tower();
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,6);
  t->setTarget(e);
  EXPECT_EQ(NULL,t->getTarget());
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_EQ(e,t->getTarget());
  delete t,e;
}

TEST(Tower, IsTargetInRange) {
  Tower* t = new Tower();
  EXPECT_FALSE(t->isTargetInRange());
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_TRUE(t->isTargetInRange());
  e->setPosition(0,6);
  EXPECT_FALSE(t->isTargetInRange());
  delete t,e;
}

TEST(Tower, FireAtTarget) {
  Tower* t = new Tower();
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_EQ(100,e->getHealth());
  t->fireAtTarget();
  EXPECT_EQ(90,e->getHealth());
  e->setPosition(0,6);
  t->fireAtTarget();
  EXPECT_EQ(90,e->getHealth());
  delete t,e;
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

TEST(Entity, Health) {
  Entity* e = NULL;
  e = new Entity();
  EXPECT_EQ(100,e->getHealth());
  EXPECT_TRUE(e->alive());
  e->setHealth(e->getHealth()-50);
  EXPECT_EQ(50,e->getHealth());
  EXPECT_TRUE(e->alive());
  e->setHealth(e->getHealth()-50);
  EXPECT_EQ(0,e->getHealth());
  EXPECT_FALSE(e->alive());
  delete e;
}

TEST(Path, CreatePath) {
  Path* p = NULL;
  p = new Path();
  ASSERT_TRUE(p != NULL);
  delete p;
}

TEST(Path, SetPosition) {
  Path* p = NULL;
  p = new Path();
  p->setPosition(1,2);
  EXPECT_EQ(1,p->getPosition()[0]);
  EXPECT_EQ(2,p->getPosition()[1]);
  delete p;
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
  t->setPosition(1,1);
  m->addTower(t);

  ASSERT_EQ(t,m->getTower(0));
  delete m;
  delete t;
}

TEST(Map, getNumTowers) {
  Map* m = new Map();
  Tower* t = new Tower();
  t->setPosition(1,1);
  EXPECT_EQ(0,m->getNumTowers());
  m->addTower(t);
  EXPECT_EQ(1,m->getNumTowers());
  delete m;
  delete t;
}

TEST(Map, getNumEntities) {
  Map* m = new Map();
  Entity* e = new Entity();

  EXPECT_EQ(0,m->getNumEntities());
  m->addEntity(e);
  EXPECT_EQ(1,m->getNumEntities());
  delete m, e;
}

TEST(Map, addTowerOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t1 = new Tower();
  t1->setPosition(1,1);
  Tower* t2 = new Tower();
  t2->setPosition(1,1);

  EXPECT_TRUE(m->addTower(t1));
  EXPECT_FALSE(m->addTower(t2));

  delete m;
  delete t1, t2;
}

TEST(Map, addTowerOnPath) {
  Map* m = NULL;
  m = new Map();

  Tower* t1 = new Tower();
  t1->setPosition(2,2);
  Tower* t2 = new Tower();
  t2->setPosition(1,1);
  Path* p = new Path();
  p->setPosition(1,1);
  EXPECT_TRUE(m->addPath(p));
  EXPECT_TRUE(m->addTower(t1));
  EXPECT_FALSE(m->addTower(t2));

  delete m;
  delete t1, t2;
  delete p;
}

TEST(Map, addTowerNonOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t1 = new Tower();
  t1->setPosition(1,0);
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
  t->setPosition(1,1);
  Entity* e = new Entity();
  EXPECT_TRUE(m->addTower(t));
  e->setPosition(1,1);
  EXPECT_FALSE(m->addEntity(e));

  delete m;
  delete t, e;
}

TEST(Map, addEntityNonOverlappingPosition) {
  Map* m = NULL;
  m = new Map();

  Tower* t = new Tower();
  t->setPosition(1,1);
  Path* p = new Path();
  p->setPosition(0,1);
  EXPECT_TRUE(m->addPath(p));
  Entity* e1 = new Entity();
  Entity* e2 = new Entity();
  e1->setPosition(0,1);
  e2->setPosition(0,1);

  EXPECT_TRUE(m->addTower(t));
  EXPECT_TRUE(m->addEntity(e1));
  EXPECT_TRUE(m->addEntity(e2));

  delete m;
  delete t, e1, e2, p;
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

  Path* p = new Path();

  p->setPosition(10,0);
  EXPECT_FALSE(m->addPath(p));

  p->setPosition(0,20);
  EXPECT_FALSE(m->addPath(p));

  p->setPosition(1,1);
  EXPECT_TRUE(m->addPath(p));
  delete m, p;
}

TEST(Map, getClosestEntity) {
  Map* m = new Map();
  m->setSize(10,20);

  Entity* e1 = new Entity();
  Entity* e2 = new Entity();

  Path* p1 = new Path();
  p1->setPosition(9,0);
  Path* p2 = new Path();
  p2->setPosition(0,9);

  EXPECT_TRUE(m->addPath(p1));
  EXPECT_TRUE(m->addPath(p2));

  e1->setPosition(9,0);
  e2->setPosition(0,9);

  EXPECT_TRUE(m->addEntity(e1));
  EXPECT_TRUE(m->addEntity(e2));

  EXPECT_EQ(e1,m->getClosestEntity(9,1));
  EXPECT_EQ(e2,m->getClosestEntity(1,9));
  delete m, e1, e2, p1, p2;
}

TEST(Map, startPoint) {
  Map* m = new Map();
  m->setSize(10,20);

  EXPECT_TRUE(m->setStartPoint(5,0));
  EXPECT_EQ(5,m->getStartPoint()[0]);
  EXPECT_EQ(0,m->getStartPoint()[1]);
  EXPECT_FALSE(m->setStartPoint(11,20));
  EXPECT_EQ(5,m->getStartPoint()[0]);
  EXPECT_EQ(0,m->getStartPoint()[1]);
  delete m;
}

TEST(Map, goalPoint) {
  Map* m = new Map();
  m->setSize(10,20);

  EXPECT_TRUE(m->setGoalPoint(5,19));
  EXPECT_EQ(5,m->getGoalPoint()[0]);
  EXPECT_EQ(19,m->getGoalPoint()[1]);
  EXPECT_FALSE(m->setGoalPoint(10,21));
  EXPECT_EQ(5,m->getGoalPoint()[0]);
  EXPECT_EQ(19,m->getGoalPoint()[1]);
  delete m;
}

TEST(Map, entityOnStartPoint) {
  Map* m = new Map();
  Entity* e = new Entity();

  EXPECT_EQ(0,m->getStartPoint()[0]);
  EXPECT_EQ(0,m->getStartPoint()[1]);

  EXPECT_TRUE(m->addEntity(e));

  delete m,e;
}

TEST(Map, addPath) {
  Map* m = new Map();

  //due to startPoint and goalPoint
  EXPECT_EQ(2,m->getNumPaths());

  Path* p = new Path();
  p->setPosition(1,1);

  m->addPath(p);
  ASSERT_EQ(p,m->getPath(2));
  EXPECT_EQ(3,m->getNumPaths());
  delete m;
  delete p;
}

TEST(Map, addEntityOffPath) {
  Map* m = NULL;
  m = new Map();

  Path* p = new Path();
  p->setPosition(1,1);
  Entity* e = new Entity();
  e->setPosition(1,1);

  EXPECT_FALSE(m->addEntity(e));
  EXPECT_TRUE(m->addPath(p));
  EXPECT_TRUE(m->addEntity(e));

  delete m;
  delete p, e;
}

TEST(Sim, CreateSim) {
  Sim* s = NULL;
  s = new Sim();
  ASSERT_TRUE(s != NULL);
  delete s;
}

TEST(Sim, CreateMap) {
  Sim* s = new Sim();
  ASSERT_TRUE(s->getMap() != NULL);
  delete s;
}

TEST(Sim, PopulateMap) {
  Sim* s = new Sim();
  EXPECT_EQ(0,s->getMap()->getNumTowers());
  EXPECT_TRUE(s->populateMap());
  EXPECT_EQ(5,s->getMap()->getNumTowers());
  delete s;
}
