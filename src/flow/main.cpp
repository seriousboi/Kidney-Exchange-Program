#include <iostream>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "graph.h"
#include "mincost.h"
#include "tests.h"
using namespace std;



int main()
{
  testInstance("../../data/fewInstances/00036-00000001.wmd",true);
  //testAllInstances("../../data/kidney",true);
  return 0;
}
