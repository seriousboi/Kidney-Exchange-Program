#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "model.h"
#include "tests.h"
using namespace std;



int main(int argc, char *argv[])
{
  //testInstance("../../data/kidney","00036-00000199.wmd",3,false);
  int maxCycleSize = 3;
  bool relaxation = false;
  int step = 0;
  vector<KepTest> results = testAllInstances("../../data/kidney",maxCycleSize,relaxation,false,step);

  return 0;
}
