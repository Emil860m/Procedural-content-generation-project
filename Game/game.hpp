#include "state.hpp"
#include <cassert>
#include <iostream>
using namespace std;
void move(State *current_state, direction dir, Position block_pos);

bool is_move_legal(State *current_state, direction dir, Position block_pos);