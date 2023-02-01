#include <vector>
#include <string>
using namespace std;

#ifndef kepInstanceFile
#define kepInstanceFile



class KepInstance
{
  public:
    int nbCouples;
    int nbTransplants;
    vector<vector<int>> validTransplants;
    vector<int> transplantsBenefits;

    KepInstance();
    KepInstance(string fileName);
    void print();
};



#endif
