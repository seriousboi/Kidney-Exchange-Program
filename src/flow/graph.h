#include <unordered_map>
#include <vector>
#include "../common/kepInstance.h"
using namespace std;

#ifndef graphFile
#define graphFile



class Arc
{
  public:
    int flow;
    int cost; /* nos coûts sont entier dans la librairie, oups ¯\_(ツ)_/¯ , pas trop grave considérant qu'on étudie le cas où tout les coûts sont 1 */
    int capacity;
    int residualCapacity;

    int pairId; /* indice de l'arc inverse parmis le vecteur d'arcs qui vont dans l'autre sens */

    Arc(int capacity,int cost);
    void print();
};



class Graph
{
  public:
    int nbVertices;
    vector<int> productions;
    vector<unordered_map<int,vector<Arc>>> vertices;

    int sourceIndex; /* identifiants du la super source et du super puit si il existent, -1 sinon */
    int sinkIndex;

    int maxDist; /* valeur qui sert à remplacer INT_MAX dans les algorithmes, c'est n'est pas la distance maximale mesurable dans le graphe mais un majorant de celle ci */

    Graph(int nbVertices);
    Graph(string filename); /* ne focntionne pas sur les fichiers KEP, utiliser le constructeur qui prend un objet KepInstance */
    Graph(KepInstance instance); /* créé le graphe d'une instance de KEP (avec les arcs négatifs transformés) */
    void initMaxDist();
    void addSuperSourceSink();
    void symmetrisation();
    void addArc(int start,int end,int capacity,int cost);
    void increaseFlow(int increase,int start,int end);
    bool isFlowPassing(int start,int end);
    void print();
};



#endif
