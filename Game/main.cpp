#include <iostream>
#include <string>
#include "game.hpp"
using namespace std;

int main() {
    string str = "00000020000060606000006064600010656261600050407000";
    State state = state_from_string(str, 5, 5);
    State *ptr = &state;
    is_move_legal(ptr, RIGHT, ptr->player_pos);
    cout << str + "\n";
    cout << string_from_state(ptr);
    return 0;
}
