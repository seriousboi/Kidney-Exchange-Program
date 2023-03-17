#include <unordered_map>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"



struct ModelAndVariables
{
  GRBModel model;
  vector<unordered_map<int,GRBVar>> arcVars;
  vector<vector<GRBVar>> cycleVars;
};



ModelAndVariables solveModel(KepInstance & instance,int maxCycleSize);
KepSolution solveModel(GRBModel & model);
