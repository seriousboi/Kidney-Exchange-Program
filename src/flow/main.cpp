#include <iostream>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "graph.h"
#include "mincost.h"
using namespace std;



int main(int nbArgs,char **values)
{
  KepInstance testInstance("../data/fewInstances/00036-00000001.wmd");
  Graph testGraph(testInstance);
  pccs(testGraph);
  KepSolution testSol = getSolutionFromGraph(testGraph,testInstance);
  testSol.print();
  return 0;
}
