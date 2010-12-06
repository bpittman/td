#include <stdlib.h>
#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <mpi.h>

#include "sim.hpp"

typedef std::pair<std::string, BigSim*> SimPair;

#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   ((tv2.tv_usec-tv1.tv_usec)+((tv2.tv_sec-tv1.tv_sec)*1000000))
#define TIMER_STOP      gettimeofday(&tv2, (struct timezone*)0)
struct timeval tv1,tv2;

int main(int argc, char **argv)
{
   MPI_Status status;
   int numtasks, rank;

   MPI_Init(&argc,&argv); // initalize MPI environment
   MPI_Comm_size(MPI_COMM_WORLD,&numtasks); //get total number of processes
   MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get process identity number

   srand(rank);
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
   
   TIMER_CLEAR;
   TIMER_START;

   //create Sim pool
   if(rank==0) {
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
   }

   int buff[poolSize*numtasks][46]; //15 towers (x,y) + tower type + entitiesAtGoal
   int local[poolSize/numtasks][46];

   for(int iter=0;iter<iterations;++iter) {
      if(rank==0) {
         //find average
         double avg=0;
         int zeros = 0;
         for(int i=0;i<pool->size();++i) {
            avg+=pool->at(i)->entitiesAtGoal();
            if(pool->at(i)->entitiesAtGoal()==0) {
            }
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
         for(int i=0;i<tournaments;++i) {
            winners->at(i)->encodeForMPI(buff[i]);
         }
         winners->clear();
         winnersMap->clear();
         for(int i=0;i<pool->size();++i) {
            delete pool->at(i);
         }
      }

      //scatter to all ranks
      MPI_Scatter(buff,tournaments/numtasks*46,MPI_INT,
                  local,tournaments/numtasks*46,MPI_INT,
                  0,MPI_COMM_WORLD);

      //rebuild Sims
      pool->clear();
      poolMap->clear();
      for(int i=0;i<tournaments/numtasks;++i) {
         BigSim* s = new BigSim;
         s->setTowersFromList(local[i],15*3);
         s->overrideEntitiesAtGoal(local[i][15*3]);
         pool->push_back(s);
         poolMap->insert(SimPair(s->getTowerListString(),s));
      }

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

      //gather from all ranks
      for(int i=0;i<poolSize;++i) {
         pool->at(i)->encodeForMPI(buff[i]);
      }
      for(int i=0;i<poolSize;++i) {
         delete pool->at(i);
      }
      pool->clear();
      poolMap->clear();
      MPI_Gather(buff,poolSize*46,MPI_INT,buff,poolSize*46,MPI_INT,0,MPI_COMM_WORLD);

      //rebuild Sims
      if(rank==0) {
         for(int i=0;i<poolSize*numtasks;++i) {
            BigSim* s = new BigSim;
            s->setTowersFromList(buff[i],15*3);
            s->overrideEntitiesAtGoal(buff[i][15*3]);
            pool->push_back(s);
            poolMap->insert(SimPair(s->getTowerListString(),s));
         }
      }
   }

   TIMER_STOP;

   if(rank==0) {
      //find & print best Sim
      best = 100;
      bestSim = NULL;
      for(int i=0;i<pool->size();++i) {
         if(pool->at(i)->entitiesAtGoal() < best) {
            best = pool->at(i)->entitiesAtGoal();
	    bestSim = pool->at(i);
         }
      }
      if(bestSim) {
         std::cout << bestSim->getMap()->print();
         std::cout << best << std::endl;
      }
      std::cout << std::setprecision(8) <<  TIMER_ELAPSED/1000000.0 << std::endl;
   }
   MPI_Finalize();
   return 0;
}
