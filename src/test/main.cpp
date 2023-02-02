#include<iostream>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
using namespace std;



int main(){
  string fileName = "../../data/fewInstances/00036-00000001.wmd";
  KepInstance testInstance(fileName);
  testInstance.print();

  vector<int> indexes = {0,1,9,30};
  KepSolution testSolution(indexes,testInstance);
  testSolution.print();
  cout << testSolution.getSolutionBenefit() << endl;

  string resolutionName = "mano";
  KepTest testest(fileName,resolutionName,testInstance,testSolution,3,false,1);
  testest.print();
  return 0;
}
