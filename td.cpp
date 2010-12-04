#include <stdlib.h>
#include <iostream>
#include <vector>

#include "sim.hpp"

int main(int argc, char **argv)
{
   srand(1);
   std::vector<BigSim*> pool;
   int poolSize = 100;
   int oldPoolSize;

   //create Sim pool
   for(int i=0;i<poolSize;++i) {
      BigSim* sim = new BigSim;
      pool.push_back(sim);
      while(sim->activeEntities()) sim->tick();
   }

   for(int iter=0;iter<10;++iter) {

      //find average
      double avg=0;
      for(int i=0;i<pool.size();++i) {
         avg+=pool[i]->entitiesAtGoal();
      }
      avg/=pool.size();
      std::cout << avg << std::endl;

      //remove some of the worst sims
      for(int i=0;i<pool.size();++i) {
         if(pool[i]->entitiesAtGoal() > avg) {
	    delete pool[i];
	    pool.erase(pool.begin()+i);
	 }
      }

      //mutate/crossover to refill pool
      int oldPoolSize = pool.size();
      double prevScore = 0;
      while(pool.size() < poolSize) {
         BigSim* sim = new BigSim;
	 if(rand()>.5) {
	    int i = rand()%oldPoolSize;
            sim->setTowersFromList(pool[i]->getTowerList(),
	                           pool[i]->getMap()->getNumTowers());
	    sim->mutateTower();
	    prevScore = pool[i]->entitiesAtGoal();
	 }
	 else {
	    int i = rand()%oldPoolSize;
	    int j = rand()%oldPoolSize;
            sim->crossoverTowers(pool[i],pool[j]);
	    prevScore = (pool[i]->entitiesAtGoal()+pool[j]->entitiesAtGoal())/2.;
	 }
	 while(sim->activeEntities()) sim->tick();
	 if(0) {
	    delete sim;
	 }
	 else {
	    pool.push_back(sim);
	 }
      }
   }

   //find & print best Sim
   int best = 100;
   BigSim* bestSim = NULL;
   for(int i=0;i<poolSize;++i) {
      if(pool[i]->entitiesAtGoal() < best) {
         best = pool[i]->entitiesAtGoal();
	 bestSim = pool[i];
      }
   }

   if(bestSim) {
      std::cout << bestSim->getMap()->print();
      std::cout << best << std::endl;
   }

   return 0;
}
