#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
using namespace std;



int main() {
  cout << "modèle PLNE ici\n";

  /* test */
  GRBEnv env = GRBEnv(true);
  env.start();
  GRBModel model = GRBModel(env);

  GRBVar x = model.addVar(0,9,0,GRB_CONTINUOUS,"x");
  GRBVar y = model.addVar(0,4,0,GRB_CONTINUOUS,"y");

  GRBLinExpr obj = 2*x + 3*y;
  model.setObjective(obj, GRB_MAXIMIZE);

  GRBLinExpr contr = 3*x + 4*y;
  model.addConstr(contr<=30,"contrainte");

  model.optimize();

  cout << "x " << x.get(GRB_DoubleAttr_X) << ", y " << y.get(GRB_DoubleAttr_X) << endl;

  return 0;
}
