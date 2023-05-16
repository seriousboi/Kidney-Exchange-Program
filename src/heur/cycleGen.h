#include<iostream>
#include <vector>
#include "../common/kepInstance.h"
using namespace std;

#ifndef heurFile
#define heurFile



struct CycleSet
{
  vector<vector<int>> * cycles;
  vector<vector<int>> * cyclesFromVertex;
};



CycleSet generateCycles(KepInstance & instance,int maxCycleSize,int maxCycleAmount);
void findCycles(KepInstance & instance,CycleSet & cycleSet,int end,int currentVertex,vector<int> & visitedVertices,vector<bool> & verticesHaveEnouhCycles,int maxCycleAmount,int depth);
bool isIn(vector<int> list,int target);
bool alreadyEnoughCyclesForOneOfTheVertices(vector<bool> & verticesHaveEnouhCycles,vector<int> & cycle); /* indique si l'un des sommet du cycle à déjà rempli son quota de cycles dans l'ensemble de cycles générés */
void updateCycleCount(CycleSet & cycleSet,vector<bool> & verticesHaveEnouhCycles,vector<int> & cycleAdded,int maxCycleAmount);
void printCycleSet(CycleSet & cycleSet);



#endif
