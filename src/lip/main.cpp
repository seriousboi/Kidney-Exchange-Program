#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "model.h"
#include "tests.h"
using namespace std;



int main(int argc, char *argv[])
{
  //testInstance("../../data/fewInstances/00036-00000001.wmd",4);
  //testInstance(argv[0],20,true);
  int maxCycleSize = 3;
  bool relaxation = false;
  int step = 75;
  vector<KepTest> results = testAllInstances("../../data/kidney",maxCycleSize,relaxation,false,step);

  /*
  for(KepTest result:results)
  {
    result.writeInFile(result.name + ".sol");
  }
  */

  return 0;
}
