rm kep.exe

g++ -c ../src/kepInstance.cpp ../src/main.cpp
g++ kepInstance.o main.o -o kep.exe

rm kepInstance.o main.o

./kep.exe
