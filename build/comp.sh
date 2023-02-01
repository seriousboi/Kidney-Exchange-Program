rm kep.exe

g++ -c ../src/common/kepInstance.cpp ../src/test/main.cpp
g++ kepInstance.o main.o -o kep.exe

rm kepInstance.o main.o

./kep.exe
