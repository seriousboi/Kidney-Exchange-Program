#include<iostream>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "cycleGen.h"
#include "stableCycles.h"
#include "tests.h"
using namespace std;



int main(){
  //string directoryPath = "../../data/fewInstances";
  string directoryPath = "../../data/kidney";
  //string fileName = "00036-00000031.wmd"; //32
  //string fileName = "00036-00000199.wmd"; //500
  //string fileName = "00036-00000253.wmd"; //1000
  //string fileName = "00036-00000288.wmd"; //2000

  //int maxCycleSize = 3;
  //int maxCycleAmount = -1;
  //bool printCycles = true;
  //testInstance(directoryPath,fileName,maxCycleSize,maxCycleAmount,printCycles);

  testAllInstances(directoryPath,3,-1);
  return 0;
}
