#include<iostream>
#include <string>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "side.h"
using namespace std;



int main(){
  string fileName = "../../data/fewInstances/00036-00000001.wmd";
  KepInstance testInstance(fileName);
  testInstance.print();

  return 0;
}
