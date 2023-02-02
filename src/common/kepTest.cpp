#include<iostream>
#include <string>
#include <glob.h>
#include "kepInstance.h"
#include "kepSolution.h"
#include "kepTest.h"
using namespace std;



vector<string> getFileNames(string directoryPath) /* retourne tout les noms d'instance (.wmd) */
{
  vector<string> fileNames(0);

  glob_t globResult;
  glob((directoryPath+"/*").c_str(),GLOB_TILDE,NULL,&globResult);

  for(int index=0;index<globResult.gl_pathc;++index)
  {
    string fileName = string(globResult.gl_pathv[index]);
    if(fileName.substr(fileName.length()-4,4) == ".wmd")
    {
      fileNames.push_back(fileName);
    }
  }
  return fileNames;
}



KepTest::KepTest()
{
  name = "Anonymous";
  resolutionName = "Unknown";

  nbCouples = -1;
  nbValidTransplants = -1;
  maxCycleSize = -1;

  solutionValue = 0;
  optimumReached = false;
  timeTaken = -1;

  instanceRef = NULL;
  solutionRef = NULL;
}



KepTest::KepTest(string name,string resolutionName,KepInstance & instance,KepSolution & solution,int maxCycleSize,bool optimumReached,int timeTaken)
{
  this->name = name;
  this->resolutionName = resolutionName;

  nbCouples = instance.nbCouples;
  nbValidTransplants = instance.nbTransplants;
  this->maxCycleSize = maxCycleSize;

  solutionValue = solution.getSolutionBenefit();
  this->optimumReached = optimumReached;
  this->timeTaken = timeTaken;

  instanceRef = &instance;
  solutionRef = &solution;
}



void KepTest::print()
{
  cout << "Instance: " << name << endl;
  cout << "Resolution: " << resolutionName << endl;
  cout << "Couples: " << nbCouples << endl;
  cout << "Potential transplants: " << nbValidTransplants << endl;
  cout << "Maximum cycle size: " << maxCycleSize << endl;
  if(optimumReached){cout << "Optimum: reached\n";}
  else{cout << "Optimum: not found\n";}
  cout << "Benefit: " << solutionValue << endl;
  cout << "Time: " << timeTaken << "s\n";
}
