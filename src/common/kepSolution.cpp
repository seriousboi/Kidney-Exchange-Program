#include<iostream>
#include "kepInstance.h"
#include "kepSolution.h"
using namespace std;



KepSolution::KepSolution()
{
  nbTransplants = 0;
  instanceRef = NULL;
}



KepSolution::KepSolution(vector<vector<int>> chosenTransplants,KepInstance & instance)
{
  nbTransplants = chosenTransplants.size();

  instanceRef = &instance;

  this->chosenTransplants = chosenTransplants; /* pas sûr qu'il se passe ce qu'on ai envie en mémoire */

  transplantsIndexes = vector<int>(nbTransplants,-1);

  for(int chosenTranspIndex=0;chosenTranspIndex<nbTransplants;++chosenTranspIndex) /* double boucle très moche mais nécessaire pour ce constructeur */
  {
    for(int validTranspInex=0;validTranspInex<instance.nbTransplants;++validTranspInex)
    {
      int chosenDonor = chosenTransplants[chosenTranspIndex][0];
      int chosenReceiver = chosenTransplants[chosenTranspIndex][1];
      int validDonor = instance.validTransplants[validTranspInex][0];
      int validReceiver = instance.validTransplants[validTranspInex][1];

      if(chosenDonor == validDonor and chosenReceiver == validReceiver)
      {
        transplantsIndexes[chosenTranspIndex] = validTranspInex;
      }
    }
  }
}



KepSolution::KepSolution(vector<int> transplantsIndexes,KepInstance & instance)
{
  nbTransplants = transplantsIndexes.size();

  instanceRef = &instance;

  this->transplantsIndexes = transplantsIndexes;

  chosenTransplants = vector<vector<int>>(nbTransplants,vector<int>(2));

  for(int chosenTranspIndex=0;chosenTranspIndex<nbTransplants;++chosenTranspIndex)
  {
    int transplantsIndex = transplantsIndexes[chosenTranspIndex];
    chosenTransplants[chosenTranspIndex] = instance.validTransplants[transplantsIndex];
  }
}



bool KepSolution::checkSolution(int maxCycleSize)
{
  return false; /* todo */
}



float KepSolution::getSolutionBenefit()
{
  if(instanceRef == NULL)
  {
    cout << "NULL pointer as reference, solution does not know its instance\n";
  }
  float benefit = 0;

  for(int chosenTranspIndex=0;chosenTranspIndex<nbTransplants;++chosenTranspIndex)
  {
    int transpIndex = transplantsIndexes[chosenTranspIndex];
    benefit += instanceRef->transplantsBenefits[transpIndex];
  }
  return benefit;
}



void KepSolution::print()
{
  cout << "KEP solution\n";
  cout << nbTransplants << " transplants chosen\n";
  for(int chosenTranspIndex=0;chosenTranspIndex<nbTransplants;++chosenTranspIndex)
  {
    cout << chosenTransplants[chosenTranspIndex][0] << " -> " << chosenTransplants[chosenTranspIndex][1] << endl;
  }
}
