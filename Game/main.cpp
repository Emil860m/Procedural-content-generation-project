#include <iostream>
#include <string>
#include "solver.hpp"
using namespace std;

int main() {
    string str = "00000020000060606000006064600010656261600050407000";
    State state = state_from_string(str, 5, 5);
    State *ptr = &state;
    cout << str + "\n";
    solve(ptr);
    return 0;
}
