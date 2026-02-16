#include <iostream>
#include <unordered_map>
#include "solver.hpp"
using namespace std;

int main() {
    string str = "00000020000060606000006064600010656261600050406000";
    State state = state_from_string(str, 5, 5);
    State *ptr = &state;
    cout << str + "\n";
    std::unordered_map<string, directions> game_states = {};
    
    solve(ptr, &game_states);
    cout << game_states.size();
    //group_gamestates(&game_states);
    return 0;
}
