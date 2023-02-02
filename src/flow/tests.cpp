#include <iostream>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "graph.h"
#include "mincost.h"
#include "tests.h"
using namespace std;



void testInstance(string fileName,bool printSolution)
{
  KepInstance instance(fileName);
  Graph graph(instance);
  pccs(graph);
  KepSolution solution = getSolutionFromGraph(graph,instance);
  if(printSolution)
  {
    solution.print();
  }
}
