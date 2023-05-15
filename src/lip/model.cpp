#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include "model.h"
using namespace std;



SolutionWithStatus solveModel(KepInstance & instance,int maxCycleSize)
{
  if(maxCycleSize == -1)
  {
    maxCycleSize = instance.nbCouples;
  }
  GRBEnv env = GRBEnv(true); /* initialisation */
  env.set("OutputFlag","0"); /* chut */
  env.start();
  GRBModel model = GRBModel(env);

  /* variables de décisions du choix des arcs */
  vector<unordered_map<int,GRBVar>> arcVars(instance.nbCouples);
  vector<unordered_map<int,GRBVar>> inArcVars(instance.nbCouples); /* arcs entrants */
  for(int transpIndex=0;transpIndex<instance.nbTransplants;transpIndex++)
  {
    int i = instance.validTransplants[transpIndex][0];
    int j = instance.validTransplants[transpIndex][1];
    arcVars[i][j] = model.addVar(0,1,1,GRB_BINARY,"x("+to_string(i)+","+to_string(j)+")");
    inArcVars[j][i] = arcVars[i][j];
  }

  /* variables de décisions d'appartenance aux cycles des sommets */
  int cyclesAmountUpperBound = ceil(instance.nbCouples/2)+1;
  vector<vector<GRBVar>> cycleVars(instance.nbCouples,vector<GRBVar>(cyclesAmountUpperBound));
  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  {
    for(int cycleIndex=0;cycleIndex<cyclesAmountUpperBound;++cycleIndex)
    {
      cycleVars[coupleIndex][cycleIndex] = model.addVar(0,1,0,GRB_BINARY,"y("+to_string(coupleIndex)+","+to_string(cycleIndex)+")");
    }
  }

  /* contraintes */
  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  {
    GRBLinExpr out; /* somme des arc sortants */
    for(pair<int,GRBVar> keyAndVariable: arcVars[coupleIndex])
    {
      out += keyAndVariable.second;
    }
    GRBLinExpr in; /* somme des arc entrants */
    for(pair<int,GRBVar> keyAndVariableAdress: inArcVars[coupleIndex])
    {
      in += keyAndVariableAdress.second;
    }

    /* contraintes de cycle, autant d'arc entrants que sortants */
    model.addConstr(in==out,"vertex "+to_string(coupleIndex)+" cycle cstr");
    /* contraintes de limitations, un arc sortant au plus par sommet */
    model.addConstr(out<=1,"vertex "+to_string(coupleIndex)+" limit cstr");

    GRBLinExpr classSum; /* somme des variables de décisions d'appartenance aux cycles */
    for(int cycleIndex=0;cycleIndex<cyclesAmountUpperBound;++cycleIndex)
    {
      classSum += cycleVars[coupleIndex][cycleIndex];
    }

    /* contraintes sur les variables de classes, un sommet doit appartenir à une unique classe */
    model.addConstr(classSum==1,"vertex "+to_string(coupleIndex)+" class cstr");
  }

  for(int cycleIndex=0;cycleIndex<cyclesAmountUpperBound;++cycleIndex)
  {
    GRBLinExpr classSize; /* nombre de sommet dans une classe */
    for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
    {
      classSize += cycleVars[coupleIndex][cycleIndex];
    }

    /* contraintes de taille de cycle */
    model.addConstr(classSize<=maxCycleSize,"class "+to_string(cycleIndex)+" size cstr");

    for(int transpIndex=0;transpIndex<instance.nbTransplants;transpIndex++)
    {
      int i = instance.validTransplants[transpIndex][0];
      int j = instance.validTransplants[transpIndex][1];
      GRBLinExpr leq = cycleVars[i][cycleIndex] - cycleVars[j][cycleIndex] - (1-arcVars[i][j]);
      GRBLinExpr geq = cycleVars[i][cycleIndex] - cycleVars[j][cycleIndex] + (1-arcVars[i][j]);
      /* contraintes d'homogénéité, deux extrémité d'un arc pris doivent être de même classe */
      model.addConstr(leq<=0,"class "+to_string(cycleIndex)+" arc ("+to_string(i)+","+to_string(j)+") leq cstr");
      model.addConstr(geq>=0,"class "+to_string(cycleIndex)+" arc ("+to_string(i)+","+to_string(j)+") geq cstr");
    }
  }

  GRBLinExpr objective; /* fontion objectif */
  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  {
    for(pair<int,GRBVar> keyAndVariable: arcVars[coupleIndex])
    {
      objective += keyAndVariable.second;
    }
  }

  /* résolution */
  model.setObjective(objective,GRB_MAXIMIZE);
  model.optimize();

  vector<vector<int>> chosenTransplants;
  bool optimumReached = false;
  /* on regarde le status de la résolution */
  int status = model.get(GRB_IntAttr_Status);
  if(status == GRB_OPTIMAL)
  {
    optimumReached = true;
    /* construction de la solution */
    for(int transpIndex=0;transpIndex<instance.nbTransplants;transpIndex++)
    {
      int i = instance.validTransplants[transpIndex][0];
      int j = instance.validTransplants[transpIndex][1];

      int varValue = (int) arcVars[i][j].get(GRB_DoubleAttr_X); /* gurobi connait seulemnt un attribut flotant alors que la varibale est entière ? ಠ_ಠ */
      if(varValue == 1)
      {
        chosenTransplants.push_back({i,j});
      }
    }
  }

  KepSolution solution(chosenTransplants,instance);
  SolutionWithStatus SwithS = {solution,optimumReached};
  return SwithS;
}
