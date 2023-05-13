#include <iostream>
#include <string>
#include <chrono>
#include "../common/kepInstance.h"
#include "../common/kepSolution.h"
#include "../common/kepTest.h"
#include "graph.h"
#include "mincost.h"
#include "tests.h"
using namespace std;



vector<KepTest> testAllInstances(string directoryPath,bool printSolution,int startStep)
{
  vector<KepTest> tests(0);

  vector<string> fileNames = getFileNames(directoryPath);

  int step = 0;
  for(string fileName:fileNames)
  {
    if(step >= startStep)
    {
      cout << fileName << endl;
      string filePath = directoryPath+"/"+fileName;
      KepTest test = testInstance(filePath,printSolution);
      tests.push_back(test);
      test.writeInFile("../../solutions/flow/"+fileName+".sol");
      cout << step+1 << " done\n";
    }
    ++step;
  }
  return tests;
}



KepTest testInstance(string fileName,bool printSolution)
{
  KepInstance instance(fileName); /* lecture du fichier dans un objet */

  Graph graph(instance); /* création du graphe à partir de l'objet */

  chrono::steady_clock::time_point startTime; /* on mesure le temps pris par l'algo */
  chrono::steady_clock::time_point endTime;
  startTime = chrono::steady_clock::now();
  pccs(graph); /* plus courts chemins augmentants sur le graphe */
  endTime = chrono::steady_clock::now();
  int duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

  KepSolution solution = getSolutionFromGraph(graph,instance); /* on extrait la solution du graphe */
  if(printSolution){solution.print();}

  KepTest test(fileName,"flow mincost",instance,solution,-1,true,duration); /* on créé un objet test qui résume toutes les infos obtenues */
  test.print();

  return test;
}
