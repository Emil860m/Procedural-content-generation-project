#include "state.hpp"
#include <unordered_set>
using namespace std;

struct State_group
{
    std::vector<std::string> child_states;
    std::vector<std::string> connected_states;
    bool can_win = false;
    float eval = 0.0f;
    int size = 0;
    int connections = 0;
};
struct directions{
    string right;
    string left;
    string up;
    string down;
};

void solve(State *state, std::unordered_map<string, directions>* game_states, std::unordered_map<string, State_group>* groups);

void group_gamestates(std::unordered_map<string, directions>* game_states);
