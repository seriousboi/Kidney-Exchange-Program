#include<iostream>
#include "../common/kepInstance.h"
using namespace std;



int main() {
  kepInstance testInstance("../data/fewInstances/00036-00000001.wmd");
  testInstance.print();
  return 0;
}
