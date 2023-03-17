#include <iostream>
#include <string>
#include <chrono>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "tests.h"
#include "model.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,bool printSolution)
{
  vector<KepTest> tests(0);

  vector<string> fileNames = getFileNames(directoryPath);

  for(string fileName:fileNames)
  {
    tests.push_back(testInstance(fileName,maxCycleSize,printSolution));
  }
  return tests;
}



KepTest testInstance(string fileName,int maxCycleSize,bool printSolution)
{
  KepInstance instance(fileName);


  chrono::steady_clock::time_point startTime; /* on mesure le temps pris par l'algo */
  chrono::steady_clock::time_point endTime;
  startTime = chrono::steady_clock::now();
  SolutionWithStatus SwithS = solveModel(instance,maxCycleSize); /* branch and bound */
  endTime = chrono::steady_clock::now();
  int duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

  KepSolution solution = SwithS.solution;
  bool optimumReached = SwithS.optimumReached;

  if(printSolution){solution.print();}

  KepTest test(fileName,"LIP branch and bound",instance,solution,maxCycleSize,optimumReached,duration); /* on créé un objet test qui résume toutes les infos obtenues */
  test.print();

  return test;
}
