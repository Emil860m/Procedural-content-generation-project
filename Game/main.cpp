#include <iostream>
#include <unordered_map>
#include "solver.hpp"
using namespace std;

int main() {
    string str = "61006060206000606060606260606060006060606000606010";
    //string str = "00000020000060606000006064600010656261600050406000";
    State state = state_from_string(str, 5, 5);
    State *ptr = &state;
    cout << evaluate(ptr) << "\n";
    return 0;
}
