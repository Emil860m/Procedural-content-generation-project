#include "state.hpp"
#include <unordered_set>
using namespace std;

struct State_group
{
    std::unordered_set<std::string>* child_states;
    std::unordered_set<State_group>* connected_states;
    bool can_win;
    float eval;
    int size;
    int connections;
};
struct directions{
    string right;
    string left;
    string up;
    string down;
};

void solve(State *state, std::unordered_map<string, directions>* game_states);

void group_gamestates(std::unordered_map<string, directions>* game_states);
