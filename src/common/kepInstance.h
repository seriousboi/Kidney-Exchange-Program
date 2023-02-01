#include <vector>
#include <string>
using namespace std;



class kepInstance
{
  public:
    int nbCouples;
    int nbTransplants;
    vector<vector<int>> validTransplants;
    vector<int> transplantsBenefits;

    kepInstance();
    kepInstance(string fileName);
    void print();
};
