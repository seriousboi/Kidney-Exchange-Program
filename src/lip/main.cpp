#include<iostream>
#include "gurobi_c++.h"
#include "../common/kepInstance.h"
#include "model.h"
#include "tests.h"
using namespace std;



int main(int argc, char *argv[])
{
  //testInstance("../../data/fewInstances/00036-00000001.wmd",4);
  testAllInstances("../../data/kidney",3,false);
  //testInstance(argv[0],20,true);
  return 0;
}
