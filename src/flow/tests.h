#include <vector>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "graph.h"
#include "mincost.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,bool printSolution=true);
KepTest testInstance(string fileName,bool printSolution=true);
