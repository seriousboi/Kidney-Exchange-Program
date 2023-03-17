#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "model.h"
#include "tests.h"
using namespace std;



int main() {
  //KepInstance instance("../../data/fewInstances/00036-00000001.wmd");
  //solveModel(instance,30);
  testAllInstances("../../data/kidney",-1,false);
  return 0;
}
