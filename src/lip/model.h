#include <unordered_map>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"



struct SolutionWithStatus
{
  KepSolution solution;
  bool optimumReached;
};



SolutionWithStatus solveModel(KepInstance & instance,int maxCycleSize);
