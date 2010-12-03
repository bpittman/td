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

TEST(Object, Adjacent) {
   Object* o1 = new Object();
   o1->setPosition(0,0);
   Object* o2 = new Object();
   o2->setPosition(0,1);
   EXPECT_TRUE(o1->adjacent(o2));
   EXPECT_TRUE(o2->adjacent(o1));
   o2->setPosition(1,1);
   EXPECT_TRUE(o1->adjacent(o2));
   EXPECT_TRUE(o2->adjacent(o1));
   o2->setPosition(1,2);
   EXPECT_FALSE(o1->adjacent(o2));
   EXPECT_FALSE(o2->adjacent(o1));
   o2->setPosition(2,2);
   EXPECT_FALSE(o1->adjacent(o2));
   EXPECT_FALSE(o2->adjacent(o1));
}

TEST(Tower, CreateTower) {
  Tower* t = NULL;
  t = new Tower();
  ASSERT_TRUE(t != NULL);
  delete t;
}

TEST(Tower, CreateSlowTower) {
  Tower* t = NULL;
  t = new SlowTower();
  ASSERT_TRUE(t != NULL);
  delete t;
}

TEST(Tower, CreateLongTower) {
  Tower* t = NULL;
  t = new LongTower();
  ASSERT_TRUE(t != NULL);
  delete t;
}

TEST(Tower, CreateShortTower) {
  Tower* t = NULL;
  t = new ShortTower();
  ASSERT_TRUE(t != NULL);
  delete t;
}

TEST(Tower, SetPosition) {
  Tower* t = new Tower();
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

TEST(Tower, NullifyOnInvalidSetTarget) {
  Tower* t = new Tower();
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_EQ(e,t->getTarget());
  e->setPosition(0,6);
  t->setTarget(e);
  EXPECT_EQ(NULL,t->getTarget());
  delete t,e;
}

TEST(Tower, NoDeadTargets) {
  Tower* t = new Tower();
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,1);
  e->setHealth(0);
  t->setTarget(e);
  EXPECT_EQ(NULL,t->getTarget());
  e->setHealth(-1);
  t->setTarget(e);
  EXPECT_EQ(NULL,t->getTarget());
  e->setHealth(1);
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

TEST(Tower, IsTargetAlive) {
  Tower* t = new Tower();
  EXPECT_FALSE(t->isTargetAlive());
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_TRUE(t->isTargetAlive());
  e->setHealth(0);
  EXPECT_FALSE(t->isTargetAlive());
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

TEST(Tower, SlowEntity) {
  SlowTower* t = new SlowTower();
  t->setPosition(0,0);
  Entity *e = new Entity();
  e->setPosition(0,5);
  t->setTarget(e);
  EXPECT_EQ(100,e->getHealth());
  EXPECT_FALSE(e->getSlowed());
  t->fireAtTarget();
  EXPECT_EQ(100,e->getHealth());
  EXPECT_TRUE(e->getSlowed());
  delete t,e;
}

TEST(Entity, CreateEntity) {
  Entity* e = NULL;
  e = new Entity();
  ASSERT_TRUE(e != NULL);
  delete e;
}

TEST(Entity, SetPosition) {
  Entity* e = new Entity();
  e->setPosition(1,2);
  EXPECT_EQ(1,e->getPosition()[0]);
  EXPECT_EQ(2,e->getPosition()[1]);
  delete e;
}

TEST(Entity, Health) {
  Entity* e = new Entity();
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

TEST(Entity, SlowEffect) {
  Entity* e = new Entity();
  e->setPosition(0,0);
  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);
  e->setSlowed(true);
  EXPECT_TRUE(e->getSlowed());
  e->setPosition(1,0);
  EXPECT_FALSE(e->getSlowed());
  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);
  e->setPosition(1,0);
  EXPECT_EQ(1,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);
  delete e;
}

TEST(Path, CreatePath) {
  Path* p = NULL;
  p = new Path();
  ASSERT_TRUE(p != NULL);
  delete p;
}

TEST(Path, SetPosition) {
  Path* p = new Path();
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
  Map* m = new Map();
  Tower* t = new Tower();
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
  Map* m = new Map();

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
  Map* m = new Map();

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
  Map* m = new Map();

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
  Map* m = new Map();

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
  Map* m = new Map();

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
  Map* m = new Map();
  Entity* e = new Entity();

  m->addEntity(e);
  ASSERT_EQ(e,m->getEntity(0));
  delete m;
  delete e;
}

TEST(Map, MoveEntity) {
  Entity* e = new Entity();
  Map* m = new Map();
  EXPECT_TRUE(m->addEntity(e));

  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);

  Path* p = new Path();
  p->setPosition(0,1);
  EXPECT_TRUE(m->addPath(p));

  m->moveEntity(e);
  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(1,e->getPosition()[1]);
  delete m, e, p;
}

TEST(Map, objectOutOfRange) {
  Map* m = new Map();

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
  EXPECT_EQ(5,m->getStartPoint()->getPosition()[0]);
  EXPECT_EQ(0,m->getStartPoint()->getPosition()[1]);
  EXPECT_FALSE(m->setStartPoint(11,20));
  EXPECT_EQ(5,m->getStartPoint()->getPosition()[0]);
  EXPECT_EQ(0,m->getStartPoint()->getPosition()[1]);
  delete m;
}

TEST(Map, goalPoint) {
  Map* m = new Map();
  m->setSize(10,20);

  EXPECT_TRUE(m->setGoalPoint(5,19));
  EXPECT_EQ(5,m->getGoalPoint()->getPosition()[0]);
  EXPECT_EQ(19,m->getGoalPoint()->getPosition()[1]);
  EXPECT_FALSE(m->setGoalPoint(10,21));
  EXPECT_EQ(5,m->getGoalPoint()->getPosition()[0]);
  EXPECT_EQ(19,m->getGoalPoint()->getPosition()[1]);
  delete m;
}

TEST(Map, entityOnStartPoint) {
  Map* m = new Map();
  Entity* e = new Entity();

  EXPECT_EQ(0,m->getStartPoint()->getPosition()[0]);
  EXPECT_EQ(0,m->getStartPoint()->getPosition()[1]);

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
  Map* m = new Map();

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

TEST(Map, bestAdjacentPath) {
  Map* m = new Map();

  Path* p1 = new Path();
  p1->setPosition(1,0);
  EXPECT_TRUE(m->addPath(p1));
  EXPECT_EQ(p1,m->bestAdjacentPath(m->getStartPoint()));

  Path* p2 = new Path();
  p2->setPosition(1,1);
  EXPECT_TRUE(m->addPath(p2));
  EXPECT_EQ(p2,m->bestAdjacentPath(m->getStartPoint()));

  Path* p3 = new Path();
  p3->setPosition(3,3);
  EXPECT_TRUE(m->addPath(p3));
  EXPECT_EQ(NULL,m->bestAdjacentPath(p3));

  delete m,p1,p2,p3;
}

TEST(Map, print) {
   Map* m = new Map();
   std::string p = m->print();
   EXPECT_EQ(
      "S X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X G \n",
      p);
   Path* path = new Path();
   path->setPosition(1,1);
   EXPECT_TRUE(m->addPath(path));
   p = m->print();
   EXPECT_EQ(
      "S X X X X X X X X X \n"
      "X P X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X G \n",
      p);
   Tower* t= new Tower();
   t->setPosition(1,2);
   EXPECT_TRUE(m->addTower(t));
   p = m->print();
   EXPECT_EQ(
      "S X X X X X X X X X \n"
      "X P T X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X G \n",
      p);
   Entity* e= new Entity();
   e->setPosition(1,1);
   EXPECT_TRUE(m->addEntity(e));
   p = m->print();
   EXPECT_EQ(
      "S X X X X X X X X X \n"
      "X E T X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X X \n"
      "X X X X X X X X X G \n",
      p);
   delete m,path,t,e;
}

TEST(Map, closestNotIncludingGoalPoint) {
  Map* m = new Map();
  Entity* e1 = new Entity();
  e1->setPosition(9,9);
  EXPECT_TRUE(m->addEntity(e1));
  EXPECT_EQ(NULL,m->getClosestEntity(5,5));
  Entity* e2 = new Entity();
  e2->setPosition(0,0);
  EXPECT_TRUE(m->addEntity(e2));
  EXPECT_EQ(e2,m->getClosestEntity(5,5));

  delete m,e1,e2;
}

TEST(Map, IgnoreDeadMoveEntity) {
  Entity* e = new Entity();
  Map* m = new Map();
  EXPECT_TRUE(m->addEntity(e));

  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);

  Path* p = new Path();
  p->setPosition(0,1);
  EXPECT_TRUE(m->addPath(p));
  e->setHealth(0);
  m->moveEntity(e);
  EXPECT_EQ(0,e->getPosition()[0]);
  EXPECT_EQ(0,e->getPosition()[1]);
  delete m, e, p;
}

TEST(Sim, CreateSim) {
  Sim* s = NULL;
  s = new Sim();
  ASSERT_TRUE(s != NULL);
  delete s;
}

TEST(Sim, CreateBigSim) {
  BigSim* s = NULL;
  s = new BigSim();
  ASSERT_TRUE(s != NULL);
  EXPECT_EQ(50,s->getMap()->getSize()[0]);
  EXPECT_EQ(50,s->getMap()->getSize()[1]);
  EXPECT_EQ(50,s->getMap()->getNumPaths());
  delete s;
}

TEST(Sim, RunBigSim) {
  srand(1);
  BigSim* s = NULL;
  s = new BigSim();
  ASSERT_TRUE(s != NULL);
  int ticks = 0;
  while(s->activeEntities()) {
     s->tick();
     ticks++;
  }
  EXPECT_EQ(149,ticks);
  EXPECT_EQ(99,s->entitiesAtGoal());
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

TEST(Sim, CheckForGoal) {
  Sim* s = new Sim();
  EXPECT_EQ(0,s->entitiesAtGoal());
  Entity* e1 = new Entity();
  e1->setPosition(9,9);
  s->getMap()->addEntity(e1);
  EXPECT_EQ(1,s->entitiesAtGoal());
  Entity* e2 = new Entity();
  e2->setPosition(0,0);
  s->getMap()->addEntity(e2);
  EXPECT_EQ(1,s->entitiesAtGoal());
  delete s,e1,e2;
}

TEST(Sim, Spawn) {
  Sim* s = new Sim();
  EXPECT_EQ(0,s->getMap()->getNumEntities());
  for(int i=0;i<10;++i) { //10 = default numEntities in Sim
     EXPECT_TRUE(s->spawn());
     EXPECT_EQ(i+1,s->getMap()->getNumEntities());
     EXPECT_EQ(s->getMap()->getStartPoint()->getPosition()[0],
               s->getMap()->getEntity(i)->getPosition()[0]);
     EXPECT_EQ(s->getMap()->getStartPoint()->getPosition()[1],
               s->getMap()->getEntity(i)->getPosition()[1]);
  }
  EXPECT_FALSE(s->spawn());
  delete s;
}

TEST(Sim, TickSpawn) {
  Sim* s = new Sim();
  EXPECT_EQ(0,s->getMap()->getNumEntities());
  for(int i=0;i<10;++i) { //10 = default numEntities in Sim
     s->tick();
     EXPECT_EQ(i+1,s->getMap()->getNumEntities());
  }
  delete s;
}

TEST(Sim, TickMove) {
  Sim* s = new Sim();
  for(int i=1;i<9;++i) {
     Path *p = new Path();
     p->setPosition(i,i);
     EXPECT_TRUE(s->getMap()->addPath(p));
  }
  for(int i=0;i<10;++i) { //10 = default numEntities in Sim
     s->tick();
     ASSERT_EQ(i+1,s->getMap()->getNumEntities());
     EXPECT_EQ(i,s->getMap()->getEntity(0)->getPosition()[0]);
     EXPECT_EQ(i,s->getMap()->getEntity(0)->getPosition()[1]);
  }
  delete s;
}

TEST(Sim, TickFire) {
  Sim* s = new Sim();
  for(int i=1;i<9;++i) {
     Path *p = new Path();
     p->setPosition(i,i);
     EXPECT_TRUE(s->getMap()->addPath(p));
  }
  Tower* t1 = new Tower();
  t1->setPosition(1,0);
  EXPECT_TRUE(s->getMap()->addTower(t1));
  Tower* t2 = new Tower();
  t2->setPosition(0,1);
  EXPECT_TRUE(s->getMap()->addTower(t2));
  for(int i=0;i<10;++i) { //10 = default numEntities in Sim
     s->tick();
     ASSERT_EQ(i+1,s->getMap()->getNumEntities());
     if(i<4) {
        EXPECT_EQ(i,s->getMap()->getEntity(0)->getPosition()[0]);
        EXPECT_EQ(i,s->getMap()->getEntity(0)->getPosition()[1]);
        EXPECT_EQ(true,s->getMap()->getEntity(0)->alive());
     }
     else {
        EXPECT_EQ(4,s->getMap()->getEntity(0)->getPosition()[0]);
        EXPECT_EQ(4,s->getMap()->getEntity(0)->getPosition()[1]);
        EXPECT_EQ(false,s->getMap()->getEntity(0)->alive());
     }
  }
  delete s;
}

TEST(Sim, ActiveEntities) {
  Sim* s = new Sim();
  for(int i=1;i<9;++i) {
     Path *p = new Path();
     p->setPosition(i,i);
     EXPECT_TRUE(s->getMap()->addPath(p));
  }
  Tower* t1 = new Tower();
  t1->setPosition(1,0);
  EXPECT_TRUE(s->getMap()->addTower(t1));
  Tower* t2 = new Tower();
  t2->setPosition(0,1);
  EXPECT_TRUE(s->getMap()->addTower(t2));
  do {
     s->tick();
  } while(s->activeEntities());
  EXPECT_EQ(8,s->entitiesAtGoal());
  delete s;
}

TEST(Sim, MutateTower) {
  srand(1);
  Sim* s = new Sim();
  int list[8] = {0,1, 1,0, 2,0, 3,1};
  s->setTowersFromList(list,8);
  ASSERT_EQ(4,s->getMap()->getNumTowers());

  EXPECT_EQ(0,s->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(1,s->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(1,s->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(2,s->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(3,s->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(1,s->getMap()->getTower(3)->getPosition()[1]);

  s->mutateTower();

  EXPECT_EQ(0,s->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(1,s->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(1,s->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(2,s->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(6,s->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(7,s->getMap()->getTower(3)->getPosition()[1]);

  delete s;
}

TEST(Sim, CrossoverTowers) {
  srand(1);
  Sim* s1 = new Sim();
  s1->populateMap();
  ASSERT_EQ(5,s1->getMap()->getNumTowers());

  Sim* s2 = new Sim();
  s2->populateMap();
  ASSERT_EQ(5,s2->getMap()->getNumTowers());

  Sim* s3 = new Sim();
  EXPECT_EQ(0,s3->getMap()->getNumTowers());
  s3->crossoverTowers(s1,s2);
  ASSERT_EQ(5,s3->getMap()->getNumTowers());

  EXPECT_EQ(3,s1->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(6,s1->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(7,s1->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(5,s1->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(3,s1->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(5,s1->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(6,s1->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(2,s1->getMap()->getTower(3)->getPosition()[1]);

  EXPECT_EQ(9,s1->getMap()->getTower(4)->getPosition()[0]);
  EXPECT_EQ(1,s1->getMap()->getTower(4)->getPosition()[1]);

  EXPECT_EQ(2,s2->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(7,s2->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(0,s2->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(9,s2->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(3,s2->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(6,s2->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(0,s2->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(6,s2->getMap()->getTower(3)->getPosition()[1]);

  EXPECT_EQ(2,s2->getMap()->getTower(4)->getPosition()[0]);
  EXPECT_EQ(6,s2->getMap()->getTower(4)->getPosition()[1]);

  EXPECT_EQ(2,s3->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(7,s3->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(7,s3->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(5,s3->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(3,s3->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(6,s3->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(0,s3->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(6,s3->getMap()->getTower(3)->getPosition()[1]);

  EXPECT_EQ(9,s3->getMap()->getTower(4)->getPosition()[0]);
  EXPECT_EQ(1,s3->getMap()->getTower(4)->getPosition()[1]);
  delete s1, s2, s3;
}

TEST(Sim, TowerList) {
  Sim* s = new Sim();
  Tower* t1 = new Tower();
  t1->setPosition(1,0);
  EXPECT_TRUE(s->getMap()->addTower(t1));
  Tower* t2 = new Tower();
  t2->setPosition(0,1);
  EXPECT_TRUE(s->getMap()->addTower(t2));
  int *tlist = s->getTowerList();
  EXPECT_EQ(tlist[0],1);
  EXPECT_EQ(tlist[1],0);
  EXPECT_EQ(tlist[2],0);
  EXPECT_EQ(tlist[3],1);

  delete s;
  delete [] tlist;
}

TEST(Sim, SetTowersFromList) {
  Sim* s = new Sim();
  int list[8] = {0,1, 1,0, 2,0, 3,1};
  s->setTowersFromList(list,8);
  ASSERT_EQ(4,s->getMap()->getNumTowers());

  EXPECT_EQ(0,s->getMap()->getTower(0)->getPosition()[0]);
  EXPECT_EQ(1,s->getMap()->getTower(0)->getPosition()[1]);

  EXPECT_EQ(1,s->getMap()->getTower(1)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(1)->getPosition()[1]);

  EXPECT_EQ(2,s->getMap()->getTower(2)->getPosition()[0]);
  EXPECT_EQ(0,s->getMap()->getTower(2)->getPosition()[1]);

  EXPECT_EQ(3,s->getMap()->getTower(3)->getPosition()[0]);
  EXPECT_EQ(1,s->getMap()->getTower(3)->getPosition()[1]);
  delete s;
}
