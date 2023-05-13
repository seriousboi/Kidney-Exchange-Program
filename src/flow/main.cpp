#include <iostream>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "graph.h"
#include "mincost.h"
#include "tests.h"
using namespace std;



int main(int argc, char *argv[])
{
  //testInstance("../../data/fewInstances/00036-00000001.wmd",true);
  //testInstance(argv[0],true);
  testAllInstances("../../data/kidney",false,156);
  return 0;
}
