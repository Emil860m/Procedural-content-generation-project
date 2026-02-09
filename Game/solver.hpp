#include "state.hpp"

struct State_group
{
    State* child_states;
    State* connected_states;
};

void solve(State *state);
