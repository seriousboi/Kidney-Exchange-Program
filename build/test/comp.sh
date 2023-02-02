rm kep.exe

g++ -c ../../src/common/kepTest.cpp ../../src/common/kepSolution.cpp ../../src/common/kepInstance.cpp ../../src/test/main.cpp
g++ kepTest.o kepSolution.o kepInstance.o main.o -o kep.exe

rm kepTest.o kepSolution.o kepInstance.o main.o

./kep.exe
