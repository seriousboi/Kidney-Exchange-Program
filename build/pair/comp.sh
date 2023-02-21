rm pairkep.exe

g++ -c  ../../src/pair/side.cpp ../../src/common/kepTest.cpp ../../src/common/kepInstance.cpp ../../src/common/kepSolution.cpp ../../src/pair/main.cpp
g++ side.o kepInstance.o kepSolution.o kepTest.o main.o -o pairkep.exe

rm kepInstance.o kepSolution.o kepTest.o main.o side.o

./pairkep.exe
