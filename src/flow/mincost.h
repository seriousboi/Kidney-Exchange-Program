#include <unordered_set>
#include <vector>
#include "graph.h"
using namespace std;

#ifndef mincostFile
#define mincostFile



bool checkGraph(Graph & graph);  /* retourne un booléen qui indique si les flots sont valides et affiche le cout */
int cost_sol(Graph & graph);   /* retourne le coût de la solution retournée */
void pccs(Graph & graph);       /* affècte un flot de cout minimal avec l'algorithme de plus courts chemins augmentants */
vector<vector<int>>  dijkstra(Graph & graph,int start,vector<int> potentials);  /* retourne les vecteur des distances et des prédécésseurs des plus courts chemins depuis start */
int findClosestTempVertex(vector<int> distances,unordered_set<int> temporarilyTagged); /* fonction pour dijkstra, trouve le sommet avec une étiquette temporaire le plus proche du départ */
int findMaxFlowAlongPath(Graph & graph,int start,int end,vector<int> predecessors,vector<int> potentials);
void increaseAlongPath(Graph & graph,int start,int end,vector<int> predecessors,int increase);



#endif
