#include "tests.h"



vector<KepTest> testAllInstances(string directoryPath,int maxCycleSize,int maxCycleAmount,int startStep)
{
  bool printCycles = false;
  vector<KepTest> tests(0);

  vector<string> fileNames = getFileNames(directoryPath);

  int step = 0;
  for(string fileName:fileNames)
  {
    if(step >= startStep)
    {
      KepTest test = testInstance(directoryPath,fileName,maxCycleSize,maxCycleAmount,printCycles);
      tests.push_back(test);
      test.writeInFile("../../solutions/heur/k="+to_string(maxCycleSize)+"/"+to_string(maxCycleAmount)+"/"+fileName+".sol");
      cout << step+1 << "steps done\n\n";
    }
    ++step;
  }
  return tests;
}



KepTest testInstance(string directoryPath,string fileName,int maxCycleSize,int maxCycleAmount,bool printCycles)
{
  string filePath = directoryPath+"/"+fileName;
  cout << fileName << endl;
  KepInstance instance(filePath);

  chrono::steady_clock::time_point startTime; /* on mesure le temps pris par l'algo en incluant la génération de cycles */
  chrono::steady_clock::time_point endTime;
  startTime = chrono::steady_clock::now();

  instance.createAdjacencyList();
  CycleSet cycleSet = generateCycles(instance,maxCycleSize,maxCycleAmount);
  if(printCycles){printCycleSet(cycleSet);}
  int value = solveStableModel(instance,cycleSet);

  endTime = chrono::steady_clock::now();
  int duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

  KepSolution solution;
  solution.nbTransplants = value;
  solution.instanceRef = &instance;
  bool optimumReached = (maxCycleAmount == -1);

  KepTest test;
  test.name = fileName;
  test.resolutionName = "Heuristic "+to_string(maxCycleAmount)+" cycles per vertex";
  test.nbCouples = instance.nbCouples;
  test.nbValidTransplants = instance.nbTransplants;
  test.maxCycleSize = maxCycleSize;
  test.solutionValue = value;
  test.optimumReached = (maxCycleAmount == -1);
  test.timeTaken = duration;
  test.print();

  return test;
}
