echo "Compiling state"
g++ -c Game/state.cpp -o build/state.o
echo "Compiling solver"
g++ -c Game/solver.cpp -o build/solver.o
echo "Compiling game"
g++ -c Game/game.cpp -o build/game.o
echo "Compiling evolutionary"
g++ -c evolutionary/evolutionary.cpp -o build/evolutionary.o
echo "Compiling main"
g++ -c main.cpp -o build/main.o
cd build
g++ state.o game.o solver.o evolutionary.o main.o -o a.out
./a.out