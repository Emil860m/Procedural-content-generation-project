echo "Compiling state"
g++ -c state.cpp
echo "Compiling solver"
g++ -c solver.cpp
echo "Compiling game"
g++ -c game.cpp
echo "Compiling main"
g++ -c main.cpp 
g++ state.o game.o solver.o main.o -o a.out
./a.out