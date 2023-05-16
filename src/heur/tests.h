#include <iostream>
#include <string>
#include <chrono>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "cycleGen.h"
#include "stableCycles.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,int maxCycleAmount,int startStep=0);
KepTest testInstance(string directoryPath,string fileName,int maxCycleSize,int maxCycleAmount,bool printCycles=true);
