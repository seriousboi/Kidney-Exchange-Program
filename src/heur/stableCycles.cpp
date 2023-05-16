#include "stableCycles.h"



int solveStableModel(KepInstance & instance,CycleSet & cycleSet)
{
  GRBEnv env = GRBEnv(true); /* initialisation */
  //env.set("OutputFlag","0"); /* chut */
  env.start();
  GRBModel model = GRBModel(env);

  /* variables de décisions du choix des cycles */
  vector<GRBVar> cycleVars(cycleSet.cycles->size());
  for(int cycleIndex=0;cycleIndex<cycleSet.cycles->size();++cycleIndex)
  {
    cycleVars[cycleIndex] = model.addVar(0,1,1,GRB_BINARY,"x"+to_string(cycleIndex));
  }

  /* contraintes de disjonction entre les cycles */
  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  {
    GRBLinExpr disjunction;
    for(int & cycleIndex:(*(cycleSet.cyclesFromVertex))[coupleIndex])
    {
      disjunction += cycleVars[cycleIndex];
    }
    model.addConstr(disjunction <= 1,"vertex "+to_string(coupleIndex)+" disjunction");
  }

  GRBLinExpr objective; /* fontion objectif */
  for(int cycleIndex=0;cycleIndex<cycleSet.cycles->size();++cycleIndex)
  {
    objective += cycleVars[cycleIndex]*((*(cycleSet.cycles))[cycleIndex].size());
  }

  /* résolution */
  model.setObjective(objective,GRB_MAXIMIZE);
  model.optimize();

  int optimum = model.getObjective().getValue();
  return optimum;
}
