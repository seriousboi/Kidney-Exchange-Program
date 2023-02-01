#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <limits.h>
#include "../common/kepInstance.h"
#include "graph.h"
using namespace std;



Graph::Graph(KepInstance instance) /* on créé directement le graphe qui a subi la transformation des arcs négatifs */
{
  sourceIndex = -1; /* pas de super-source ou de super-puit définis por l'instant */
  sinkIndex = -1;

  nbVertices = 2*instance.nbCouples; /* on a deux sommets par couple */

  vertices = vector<unordered_map<int,vector<Arc>>>(nbVertices); /* le sommet i- est à la position 2*i, le sommet i+ est à la position (2*i)+1 */

  productions = vector<int>(nbVertices,0); /* on initialise les productions à 0, on les changera au fur et à mesure que les arcs décisionels sont ajoutés */

  for(int coupleIndex=0;coupleIndex<instance.nbCouples;++coupleIndex)
  { /* ajout des arcs limitants (i+,i-) */
    int iMinus = 2*coupleIndex;
    int iPlus = (2*coupleIndex)+1;
    int capacity = 1;
    int cost = 0;
    addArc(iPlus,iMinus,capacity,cost);
  }

  for(int transpIndex=0;transpIndex<instance.nbTransplants;++transpIndex)
  { /* ajout des arcs décisionels (j+,i-), inverse des arcs (i-,j+) */
    int i = instance.validTransplants[transpIndex][0];
    int j = instance.validTransplants[transpIndex][1];
    int iMinus = 2*i;
    int jPlus = (2*j)+1;
    int capacity = 1;
    int cost = instance.transplantsBenefits[transpIndex];
    addArc(jPlus,iMinus,capacity,cost);
    productions[iMinus] -= 1;
    productions[jPlus] += 1;
  }
  initMaxDist();
}



void Graph::initMaxDist()
{
  maxDist = 0;
  for(int vertex=0;vertex< nbVertices;++vertex)
  {
    for(auto &[neighbor,edges]:vertices[vertex])
    {
      for (int edge=0;edge<edges.size();++edge)
      {
        maxDist += abs(edges[edge].cost);
      }
    }
  }
  if(maxDist < INT_MAX/1000)
  {
    maxDist = 1+maxDist*10;
  }
  else
  {
    cout << "maxDist (" << maxDist << ") is too big, graph unfit to use theses algorithms on\n";
  }
}



void Graph::increaseFlow(int increase,int start,int end)
{
  if(increase == 0){return;} /* pour éviter les boucles infinies */

  if(not isFlowPassing(end,start)) /*on vérifie que du flot ne passe pas dans l'autre sens */
  {
    for(Arc & arc:vertices[start][end]) /* on cherche l'arc sur lequel faire passer le flot */
    {
      if(arc.capacity > 0) /* /!\ on fait la supposition qu'il existe un unique arc avec capacity > 0 entre start et end*/
      {
        arc.flow += increase;
        arc.residualCapacity -= increase;
        Arc & pairedEdge = vertices[end][start][arc.pairId];
        pairedEdge.residualCapacity += increase;
        return;
      }
    }
  }
  else
  { /* appels récursifs infinis si les deux flots sont non-nuls */
    for(Arc & arc:vertices[end][start]) /* on cherche l'arc sur lequel du flot passe */
    {
      if(arc.flow > 0) /* /!\ on fait la supposition qu'il existe un unique arc avec flow > 0 entre end et start*/
      {
        int flowReversed = min(arc.flow,increase);
        increaseFlow(-flowReversed,end,start);
        increaseFlow(increase-flowReversed,start,end);
        return;
      }
    }
  }
}



bool Graph::isFlowPassing(int start,int end) /* vérifie si du flot passe entre les sommets start et end, spécifiquement dans ce sens */
{
  for(Arc arc:vertices[start][end])
  {
    if(arc.flow > 0)
    {
      return true;
    }
  }
  return false;
}



void Graph::addArc(int start,int end,int capacity,int cost) /* ajoute l'arc du sommet start vers le sommet end */
{
  if(not(start<nbVertices and end<nbVertices and start>=0 and end>=0))
  {
    cout << "Cannot add invalid edge to graph, yikes\n";
    return;
  }
  vertices[start][end].push_back(Arc(capacity,cost));
}



void Graph::addSuperSourceSink()
{
  // 2 variables qui vont nous permettre d'avoir la production et la consommation totale
  int produit = 0;
  int consomme = 0;
  // on crée les noeuds source et puit
  unordered_map<int,vector<Arc>> source;
  unordered_map<int,vector<Arc>> puit;
  // on les ajoute à notre graphe (aux deux dernières positions)
  vertices.push_back(source);
  vertices.push_back(puit);
  sourceIndex = nbVertices;
  sinkIndex = nbVertices+1;
  nbVertices += 2;

  for (int i=0; i< nbVertices-2; ++i){   //on parcourt nootre vecteur productions
    if (productions[i]>0)
    {                     // on récupére les noeuds producteurs
      addArc(sourceIndex,i,productions[i],0);    //création des arcs du 'super' noeud vers les 'vrai' noeuds producteurs
      produit = produit + productions[i];
      productions[i] = 0;
    }
    else if (productions[i]<0)
    {                // on récupère les noeuds consommateurs
      consomme = consomme + productions[i];
      addArc(i,sinkIndex,-productions[i],0);  // création des arcs des 'vrai' noeud vers le 'super' noeud consommateur
      productions[i] = 0;
    }
  }
  // on ajoute les productions totales au vecteur des productions
  productions.push_back(produit);
  productions.push_back(consomme);
}



void Graph::symmetrisation()
{
  for(int vertex=0;vertex<nbVertices;++vertex)
  {
    for(auto & [neighbor,arcs] : vertices[vertex])
    {
      for(int arcIndex = 0;arcIndex<arcs.size();++arcIndex)
      { /* on ajoute l'arc inverse même si il y a un arc qui va dans le sens oppsé à cause des coûts */
        Arc & arc = vertices[vertex][neighbor][arcIndex];
        if(arc.capacity > 0)
        { /* en revanche on vérifie si la capacité est strictement positive pour ne pas donné d'arc inverse aux arcs inverses */
          addArc(neighbor,vertex,0,-arc.cost);
          arc.pairId = vertices[neighbor][vertex].size()-1; /* le sous index de l'arc inverse et la taille du vecteur qui le contient -1 car on vient juste d'ajouter l'arc au vecteur */
          vertices[neighbor][vertex].back().pairId = arcIndex;
        }
      }
    }
  }
}



Graph::Graph(string filename)
{
  ifstream dataStream(filename);
  if(!dataStream)
  {
    cout << "oof, cannot open file " << filename << endl;
    return;
  }

  sourceIndex = -1;
  sinkIndex = -1;

  string lineIdentifier;
  dataStream >> lineIdentifier;
  while(not dataStream.eof())
  {
    if(lineIdentifier=="p")
    {
      dataStream >> lineIdentifier; /* on saute le "min" */
      dataStream >> nbVertices;
      vertices = vector<unordered_map<int,vector<Arc>>>(nbVertices);
      productions = vector<int>(nbVertices);
      int nbEdges;
      dataStream >> lineIdentifier; /* on saute le nombre d'arcs */
    }
    else if(lineIdentifier=="n")
    {
      int vertexIndex;
      dataStream >> vertexIndex;
      vertexIndex--; /* l'indexage commence à 1 dans les fichiers */
      dataStream >> productions[vertexIndex];
    }
    else if(lineIdentifier=="a")
    {
      int startIndex,endIndex;
      dataStream >> startIndex;
      dataStream >> endIndex;
      startIndex--;
      endIndex--;
      dataStream >> lineIdentifier; /* on saute mincap */
      int capacity,cost;
      dataStream >> capacity;
      dataStream >> cost;
      addArc(startIndex,endIndex,capacity,cost);
    }
    dataStream >> lineIdentifier;
  }
  initMaxDist();
}



Graph::Graph(int nbVertices)
{
  this->nbVertices = nbVertices;
  vertices = vector<unordered_map<int,vector<Arc>>>(nbVertices);
  sourceIndex = -1;
  sinkIndex = -1;
}



void Graph::print() /* affiche les listes d'adjacences sous forme <sommet i: (voisin1,coût1) (voisin2,coût2)> */
{
  cout << "graph with " << nbVertices << " vertices\n";
  for(int vertex=0;vertex<nbVertices;++vertex)
  {
    cout << "vertex " << vertex;
    if(productions[vertex]>0)
    {
      cout << " +(" << productions[vertex] << ")";
    }
    if(productions[vertex]<0)
    {
      cout << " -(" << -productions[vertex] << ")";
    }
    cout<< ": ";

    for(auto &[neighbor,arcs] : vertices[vertex])
    {
      for(Arc & arc : arcs)
      {
        cout << "(" << neighbor << "," << arc.capacity << "," << arc.cost << ") ";
      }
    }
    cout << "\n";
  }
}



Arc::Arc(int capacity,int cost)
{
  this->capacity = capacity;
  this->cost = cost;
  flow = 0;
  residualCapacity = capacity;
  pairId = -1;
}



void Arc::print() /* affiche les détails d'un arc, mais n'affiche pas le sommet sortant et le sommet entrant */
{
  cout << "(flow:" << flow << ", cap:" << capacity << ", rescap:" << residualCapacity << ", cost:" << cost << ", pairId:" << pairId << ") ";
}
