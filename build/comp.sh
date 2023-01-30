rm kep.exe

g++ -c ../src/main.cpp
g++ main.o -o kep.exe

rm main.o

./kep.exe
