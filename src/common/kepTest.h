#include <vector>
#include <string>
#include "kepInstance.h"
#include "kepSolution.h"
using namespace std;

#ifndef kepTestFile
#define kepTestFile



class KepTest
{
  public:
    string name;
    string resolutionName;

    int nbCouples;
    int nbValidTransplants;
    int maxCycleSize;

    float solutionValue;
    bool optimumReached; /* optimum potentiellement local */
    int timeTaken; /* temps en secondes */

    KepInstance * instanceRef;
    KepSolution * solutionRef;

    KepTest();
    KepTest(string name,string resolutionName,KepInstance & instance,KepSolution & solution,int maxCycleSize,bool optimumReached,int timeTaken);
    void writeInFile(string filName);
    void print();
};


/* fonction en rapport avec les tests mais qui ne mérite pas d'être un méthode de la classe KepTest */
vector<string> getFileNames(string directoryPath); /* donne seulement les fichiers d'instance .wmd */



#endif
