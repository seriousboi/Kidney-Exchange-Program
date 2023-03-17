#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "model.h"
using namespace std;



int main() {
  string fileName = "../../data/fewInstances/00036-00000001.wmd";
  KepInstance instance(fileName);
  ModelAndVariables yayatest = solveModel(instance,2);
  return 0;
}
