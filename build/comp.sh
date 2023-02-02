rm kep.exe

g++ -c ../src/common/kepSolution.cpp ../src/common/kepInstance.cpp ../src/test/main.cpp
g++ kepSolution.o kepInstance.o main.o -o kep.exe

rm kepSolution.o kepInstance.o main.o

./kep.exe
