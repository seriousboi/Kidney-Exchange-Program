#include <vector>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,bool printSolution=true);
KepTest testInstance(string fileName,int maxCycleSize,bool printSolution=true);
