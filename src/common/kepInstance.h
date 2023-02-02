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
    vector<vector<int>> validTransplants; /* vecteur des transplants, un transplants est de la forme (i,j): donneur du couple i vers receveur du couple j */
    vector<int> transplantsBenefits;

    KepInstance();
    KepInstance(string fileName);
    void print();
};



#endif
