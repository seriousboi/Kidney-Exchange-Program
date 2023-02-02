rm flowkep.exe

g++ -c ../../src/flow/tests.cpp ../../src/flow/graph.cpp ../../src/flow/mincost.cpp ../../src/common/kepInstance.cpp ../../src/common/kepSolution.cpp ../../src/flow/main.cpp
g++ tests.o graph.o mincost.o kepInstance.o kepSolution.o main.o -o flowkep.exe

rm tests.o graph.o mincost.o kepInstance.o kepSolution.o main.o

./flowkep.exe
