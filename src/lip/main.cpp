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
  vector<KepTest> results = testAllInstances("../../data/kidney",3,false,false);

  /*
  for(KepTest result:results)
  {
    result.writeInFile(result.name + ".sol");
  }
  */

  return 0;
}
