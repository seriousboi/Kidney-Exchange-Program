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

    vector<vector<int>> transplantsList; /* liste d'adjacence du graphe correspondant, n'est pas initialisée avec le constructeur, il faut utiliser la méthode createAdjacencyList */
    bool listCreated; /* indique si la liste d'adjacence a été créée */
    void createAdjacencyList();
};



#endif
