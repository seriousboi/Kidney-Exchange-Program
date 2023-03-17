TER 2023
Problème d'échange de reins
Xiaoyu Chen, Emmanuel Ajot, Pierre Pinet



-lien vers le rapport (lecture seule):
https://fr.overleaf.com/read/ymybhkqfzcjn



-séparation en plusieurs sous projets qui ont leur propre dossier src et leur propre dossier build:

k = +infini, résolution par mincost
"flow" src/flow build/flow

k quelconque, résolution d'un programme linéaire en nombres entiers
"lip" src/lip build/lip



-pour compiler le programme sous Linux:

pour "lip" se placer dans le dossier build/lip
$CMake CMakeLists.txt
$make
$./lipkep.exe

pour "flow" se placer dans le dossier build/flow
$sh flowcomp.sh



-pour compiler le programme sous Windows:
débrouillez vous



-Ajout des fichiers d'instance:
la totalité des fichiers d'instance sont lourd il faut donc les ajouter soi-même
télécharger l'archive https://www.preflib.org/dataset/00036
décompresser l'archive
déposer le dossier "kidney" dans le dossier "data"
ce dossier sera ignoré lors des commit grâce au fichier gitignore



-todo:
utiliser des CMakeLists
faire meilleur système de tests (pouvoir couper entre deux instances et reprendre au même endroit après)
écrire les tests dans des fichiers
faire des images des graphes à partir des instances et des solutions
faire une fonction qui consigne les fichiers des résultats dans un tableur
