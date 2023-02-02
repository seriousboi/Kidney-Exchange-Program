#include<iostream>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
using namespace std;



int main() {
  KepInstance testInstance("../data/fewInstances/00036-00000001.wmd");
  testInstance.print();

  vector<int> indexes = {0,1,9,30};
  KepSolution testSolution(indexes,testInstance);
  testSolution.print();
  cout << testSolution.getSolutionBenefit() << endl;
  return 0;
}
