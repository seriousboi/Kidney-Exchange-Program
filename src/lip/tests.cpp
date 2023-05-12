#include <iostream>
#include <string>
#include <chrono>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "tests.h"
#include "model.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,bool relaxation,bool printSolution,int startStep)
{
  vector<KepTest> tests(0);

  vector<string> fileNames = getFileNames(directoryPath);

  int step = 0;
  for(string fileName:fileNames)
  {
    if(step >= startStep)
    {
      KepTest test = testInstance(directoryPath,fileName,maxCycleSize,relaxation,printSolution);
      tests.push_back(test);
      if(relaxation)
      {
        test.writeInFile("../../solutions/lip/relax/"+fileName+".sol");
      }
      else
      {
        test.writeInFile("../../solutions/lip/"+to_string(maxCycleSize)+"/"+fileName+".sol");
      }
    }
    ++step;
  }
  return tests;
}



KepTest testInstance(string directoryPath,string fileName,int maxCycleSize,bool relaxation,bool printSolution)
{
  string filePath = directoryPath+"/"+fileName;
  KepInstance instance(filePath);
  if(relaxation)
  {
    maxCycleSize = instance.nbTransplants;
  }

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
  cout << endl;
  return test;
}
