rm flowkep.exe

g++ -c ../src/flow/graph.cpp ../src/flow/mincost.cpp ../src/common/kepInstance.cpp ../src/common/kepSolution.cpp ../src/flow/main.cpp
g++ graph.o mincost.o kepInstance.o kepSolution.o main.o -o flowkep.exe

rm graph.o mincost.o kepInstance.o kepSolution.o main.o

./flowkep.exe
