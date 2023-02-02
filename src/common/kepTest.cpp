#include<iostream>
#include <string>
#include "kepInstance.h"
#include "kepSolution.h"
#include "kepTest.h"
using namespace std;



KepTest::KepTest()
{
  fileName = "Anonymous";
  resolutionName = "Unknown";

  nbCouples = -1;
  nbValidTransplants = -1;
  maxCycleSize = -1;

  solutionValue = 0;
  optimumReached = false;
  timeTaken = -1;
}



KepTest::KepTest(string fileName,string resolutionName,KepInstance & instance,KepSolution & solution,int maxCycleSize,bool optimumReached,int timeTaken)
{
  this->fileName = fileName;
  this->resolutionName = resolutionName;

  nbCouples = instance.nbCouples;
  nbValidTransplants = instance.nbTransplants;

  solutionValue = solution.getSolutionBenefit();
  this->optimumReached = optimumReached;
  this->timeTaken = timeTaken;
}



void KepTest::print()
{
  cout << "Instance: " << fileName << endl;
  cout << "Resolution: " << resolutionName << endl;
  cout << "Couples: " << nbCouples << endl;
  cout << "Potential transplants: " << nbValidTransplants << endl;
  cout << "Maximum cycle size: " << maxCycleSize << endl;
  if(optimumReached){cout << "Optimum: reached\n";}
  else{cout << "Optimum: not found\n";}
  cout << "Benefit: " << solutionValue << endl;
  cout << "Time: " << timeTaken << "s\n";
}
