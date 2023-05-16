#include <limits.h>
#include "cycleGen.h"



CycleSet generateCycles(KepInstance & instance,int maxCycleSize,int maxCycleAmount)
{
  if(maxCycleAmount == -1){maxCycleAmount = INT_MAX;}
  
  CycleSet cycleSet;
  cycleSet.cycles = new vector<vector<int>>(0);
  cycleSet.cyclesFromVertex = new vector<vector<int>>(instance.nbCouples,vector<int>(0));

  vector<bool> verticesHaveEnouhCycles(instance.nbCouples,false);

  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  {
    int depth = 2;
    while((not verticesHaveEnouhCycles[coupleIndex]) and depth <= maxCycleSize)
    {
      vector<int> visitedVertices{coupleIndex};
      findCycles(instance,cycleSet,coupleIndex,coupleIndex,visitedVertices,verticesHaveEnouhCycles,maxCycleAmount,depth);
      ++ depth;
    }
  }

  return cycleSet;
}



void findCycles(KepInstance & instance,CycleSet & cycleSet,int end,int currentVertex,vector<int> & visitedVertices,vector<bool> & verticesHaveEnouhCycles,int maxCycleAmount,int depth)
{
  for(int & neighborIndex:instance.transplantsList[currentVertex])
  {
    if(verticesHaveEnouhCycles[currentVertex]){return;}

    if(depth > 1 and neighborIndex>end  and (not isIn(visitedVertices,neighborIndex)) and (not verticesHaveEnouhCycles[neighborIndex]))
    /* (neighborIndex>end) pour ne pas avoir deux fois le meme cycle, cela suppose qu'on a trouvé tout les cycles désirés contenant les sommets d'indice plus petit, sus */
    {
      visitedVertices.push_back(neighborIndex); //ajoute le sommet voisin dans la fausse file
      findCycles(instance,cycleSet,end,neighborIndex,visitedVertices,verticesHaveEnouhCycles,maxCycleAmount,depth-1);
      visitedVertices.pop_back(); //retire le sommet voisin dans la fausse file
    }
    else if(depth == 1 and neighborIndex == end)
    {
      cycleSet.cycles->push_back(visitedVertices); //sus

      int cycleIndex = cycleSet.cycles->size() - 1;
      for(int & vertexInCycle:visitedVertices)
      {
        (*(cycleSet.cyclesFromVertex))[vertexInCycle].push_back(cycleIndex);
      }

      updateCycleCount(cycleSet,verticesHaveEnouhCycles,visitedVertices,maxCycleAmount);
    }
  }
}



bool isIn(vector<int> list,int target)
{
  for(int & element:list)
  {
    if(target == element)
    {
      return true;
    }
  }
  return false;
}



bool alreadyEnoughCyclesForOneOfTheVertices(vector<bool> & verticesHaveEnouhCycles,vector<int> & cycle)
{
  for(int & vertexInCycle:cycle)
  {
    if(verticesHaveEnouhCycles[vertexInCycle])
    {
      return true;
    }
  }
  return false;
}



void updateCycleCount(CycleSet & cycleSet,vector<bool> & verticesHaveEnouhCycles,vector<int> & cycleAdded,int maxCycleAmount)
{
  for(int & vertexInCycle:cycleAdded)
  {
    if((not verticesHaveEnouhCycles[vertexInCycle]) and ((*(cycleSet.cyclesFromVertex))[vertexInCycle].size() >= maxCycleAmount))
    {
      verticesHaveEnouhCycles[vertexInCycle] = true;
    }
  }
}



void printCycleSet(CycleSet & cycleSet)
{
  cout << "Cycles\n";
  for(int cycleIndex=0;cycleIndex<cycleSet.cycles->size();++cycleIndex)
  {
    cout << cycleIndex << ":";
    for(int & vertexInCycle:(*(cycleSet.cycles))[cycleIndex])
    {
      cout << " " << vertexInCycle << " ->";
    }
    cout << " " << (*(cycleSet.cycles))[cycleIndex][0] << endl;
  }

  cout << "Vertices in cycles\n";
  for(int coupleIndex=0;coupleIndex<cycleSet.cyclesFromVertex->size();++coupleIndex)
  {
    if((*(cycleSet.cyclesFromVertex))[coupleIndex].size()>0)
    {
      cout << coupleIndex << ":";
      for(int & cycleIndex:(*(cycleSet.cyclesFromVertex))[coupleIndex])
      {
        cout << " " << cycleIndex;
      }
      cout << endl;
    }
  }
}
