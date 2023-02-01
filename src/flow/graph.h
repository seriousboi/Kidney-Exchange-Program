#include <unordered_map>
#include <vector>
using namespace std;

#ifndef graphFile
#define graphFile



class Arc
{
  public:
    int flow;
    int cost;
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

    Graph(int nbVertices);
    Graph(string filename); /* ne focntionne pas sur les fichiers KEP */
    void addSuperSourceSink();
    void symmetrisation();
    void addArc(int start,int end,int capacity,int cost);
    void increaseFlow(int increase,int start,int end);
    bool isFlowPassing(int start,int end);
    void print();
};



#endif
