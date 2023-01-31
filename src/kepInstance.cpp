#include<iostream>
#include <fstream>
#include "kepInstance.h"
using namespace std;



kepInstance::kepInstance(string fileName)
{
  ifstream dataStream(fileName); /* ouverture du fichier */
  if(!dataStream)
  {
    cout << "oof, cannot open file '" << fileName << "'\n";
    return;
  }

  string lineIdentifier;
  bool endOfComments = false;

  while(not (dataStream.eof() or endOfComments))
  {
    dataStream >> lineIdentifier; /* on fait une boucle sur les "mots" du fichier */

    if(lineIdentifier == "NUMBER")
    {
      dataStream >> lineIdentifier;

      if(lineIdentifier == "ALTERNATIVES:")
      {
        dataStream >> nbCouples;
      }
      else if(lineIdentifier == "EDGES:")
      {
        dataStream >> nbTransplants;
        endOfComments = true; /* on arrête la boucle quand on a lu la ligne du nombre d'arcs */
        getline(dataStream,lineIdentifier); /* on passe à la ligne suivante */
      }
    }
  }

  string line; /* maintenant on lit les lignes entières à la place des mots */

  for(int index=0;index<nbCouples;++index)
  {
    getline(dataStream,line); /* on saute les lignes de nom de couple */
  }

  validTransplants = vector<vector<int>>(nbTransplants,vector<int>(2));
  transplantsBenefits = vector<int>(nbTransplants);

  for(int index=0;index<nbTransplants;++index) /* on fait une boucle sur les lignes des arcs */
  {
    getline(dataStream,line);

    int start = stoi(line.substr(0,line.find(","))); /* on extrait puis on coupe la partie du string qui nous intéresse plusieurs fois */
    line.erase(0,line.find(",")+1);
    int end = stoi(line.substr(0,line.find(",")));
    line.erase(0,line.find(",")+1);
    float benefit = stof(line);

    validTransplants[index] = {start,end};
    transplantsBenefits[index] = benefit;
  }
}



void kepInstance::print()
{
  cout << "KEP instance\n";
  cout << nbCouples << " Couples\n";
  cout << nbTransplants << " potential transplants\n";

  for(int index=0;index<nbTransplants;++index)
  {
    cout << validTransplants[index][0] << " to " << validTransplants[index][1];
    if(transplantsBenefits[index] != 1)
    {
      cout << " | " << transplantsBenefits[index];
    }
    cout << endl;
  }
  return;
}



kepInstance::kepInstance()
{
  nbCouples = 0;
  nbTransplants = 0;
}
