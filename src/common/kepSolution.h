#include <vector>
#include "kepInstance.h"
using namespace std;

#ifndef kepSolutionFile
#define kepSolutionFile



class KepSolution
{
  public:
    int nbTransplants;
    vector<int> transplantsIndexes; /* vecteur des indices des transplants choisis */
    vector<vector<int>> chosenTransplants; /* vecteur des transplants choisis */

    KepInstance * instanceRef;


    KepSolution();
    KepSolution(vector<vector<int>> chosenTransplants,KepInstance & instance); /* constructeur à partir du vecteur des transplants choisis */
    KepSolution(vector<int> chosenTransplantsIndexes,KepInstance & instance); /* constructeur à du vecteur des indices des transplants choisis */
    bool checkSolution(int maxCycleSize);
    float getSolutionBenefit();
    void print();
};



#endif
