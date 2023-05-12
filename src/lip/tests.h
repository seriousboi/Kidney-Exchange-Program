#include <vector>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,bool relaxation,bool printSolution=true,int startStep=0);
KepTest testInstance(string directoryPath,string fileName,int maxCycleSize,bool relaxation,bool printSolution=true);
