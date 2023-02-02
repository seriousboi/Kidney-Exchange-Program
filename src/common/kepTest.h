#include <string>
#include "kepInstance.h"
#include "kepSolution.h"
using namespace std;

#ifndef kepTestFile
#define kepTestFile



class KepTest
{
  public:
    string fileName;
    string resolutionName;

    int nbCouples;
    int nbValidTransplants;
    int maxCycleSize;

    float solutionValue;
    bool optimumReached; /* optimum potentiellement local */
    int timeTaken; /* temps en secondes */

    KepTest();
    KepTest(string fileName,string resolutionName,KepInstance & instance,KepSolution & solution,int maxCycleSize,bool optimumReached,int timeTaken);
    void print();
};



#endif
