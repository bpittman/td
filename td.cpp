#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>

#include "sim.hpp"

typedef std::pair<std::string, BigSim*> SimPair;

int main(int argc, char **argv)
{
   srand(1);
   std::vector<BigSim*> *pool = new std::vector<BigSim*>;
   std::map<std::string,BigSim*> *poolMap = new std::map<std::string,BigSim*>;

   std::vector<BigSim*> *winners = new std::vector<BigSim*>;
   std::map<std::string,BigSim*> *winnersMap = new std::map<std::string,BigSim*>;

   std::vector<BigSim*> *temp;
   std::map<std::string,BigSim*> *tempMap;

   int poolSize = 300;
   int tourneySize = 8;
   int tournaments = 200;
   int iterations = 10;
   int oldPoolSize, best, r;
   BigSim* bestSim;
   
   //create Sim pool
   while(pool->size() < poolSize) {
      BigSim* sim = new BigSim;
      sim->populateMap();
      
      if(poolMap->find(sim->getTowerListString())==poolMap->end()) {
         while(sim->activeEntities()) sim->tick();
         pool->push_back(sim);
	 poolMap->insert(SimPair(sim->getTowerListString(),sim));
      }
      else {
         delete sim;
      }
   }

   for(int iter=0;iter<iterations;++iter) {

      //find average
      double avg=0;
      for(int i=0;i<pool->size();++i) {
         avg+=pool->at(i)->entitiesAtGoal();
      }
      avg/=pool->size();
      std::cout << avg << std::endl;

      //remove some of the worst sims
      winners->clear();
      winnersMap->clear();
      for(int i=0;i<tournaments;++i) {
         best = 100;
         bestSim = NULL;
         for(int j=0;j<tourneySize;++j) {
	    do {
	       r = rand()%pool->size();
	    } while(winnersMap->find(pool->at(r)->getTowerListString())!=winnersMap->end());
            if(bestSim == NULL || pool->at(r)->entitiesAtGoal() <= best) {
	       bestSim = pool->at(r);
	       best = pool->at(r)->entitiesAtGoal();
	    }
	 }
         winners->push_back(bestSim);
	 winnersMap->insert(SimPair(bestSim->getTowerListString(),bestSim));
      }

      pool->clear();
      poolMap->clear();
      temp = pool;
      tempMap = poolMap;
      pool = winners;
      poolMap = winnersMap;
      winners = temp;
      winnersMap = tempMap;

      //mutate/crossover to refill pool
      int oldPoolSize = pool->size();
      double prevScore = 0;
      while(pool->size() < poolSize) {
         BigSim* sim = new BigSim;
	 if(rand()%10<1) {
	    int i = rand()%oldPoolSize;
            sim->setTowersFromList(pool->at(i)->getTowerList(),
	                           pool->at(i)->getMap()->getNumTowers()*3);
	    sim->mutateTower();
	    prevScore = pool->at(i)->entitiesAtGoal();
	 }
	 else {
	    int i = rand()%oldPoolSize;
	    int j = rand()%oldPoolSize;
            sim->crossoverTowers(pool->at(i),pool->at(j));
	    prevScore = (pool->at(i)->entitiesAtGoal()+pool->at(j)->entitiesAtGoal())/2.;
	 }
	 while(sim->activeEntities()) sim->tick();
         pool->push_back(sim);
         poolMap->insert(SimPair(sim->getTowerListString(),sim));
      }
   }

   //find & print best Sim
   best = 100;
   bestSim = NULL;
   for(int i=0;i<poolSize;++i) {
      if(pool->at(i)->entitiesAtGoal() < best) {
         best = pool->at(i)->entitiesAtGoal();
	 bestSim = pool->at(i);
      }
   }

   if(bestSim) {
      std::cout << bestSim->getMap()->print();
      std::cout << best << std::endl;
   }

   return 0;
}
