#include "game.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
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




void solve(State *state, std::unordered_map<string, directions>* game_states) {
    short x = state->size_x;
    short y = state->size_y;
    string sstr = string_from_state(state);
    std::unordered_set<std::string> seen_states{sstr};
    //std::unordered_map<string, directions> game_states = {};
    
    stack<string> st;
    st.push(sstr);
    string current;
    while (!st.empty())
    {
        current = st.top();
        st.pop();
        directions dirs;
        game_states[0].insert({current, dirs});
        for (int i = 0; i < 4; i++)
        {
            State new_state = state_from_string(current, x, y);
            State* ptr = &new_state;
            attempt_move(ptr, (direction)i);
            string str = string_from_state(ptr);
            if (!seen_states.count(str) && str != "LOST" && str != "WIN") {
                st.push(str);
            }
            seen_states.insert(str);
            switch (i)
            {
            case 0:
                game_states[0].find(current)->second.right = str;
                break;
            case 1:
                game_states[0].find(current)->second.left = str;
                break;
            case 2:
                game_states[0].find(current)->second.up = str;
                break;
            case 3:
                game_states[0].find(current)->second.down = str;
                break;
            default:
                break;
            }
        }
        
    }
}


void group_gamestates(std::unordered_map<string, directions>* game_states) {
    std::unordered_map<string, State_group> groups = {};
    for (const auto& [key, value] : game_states[0]) {
        if (auto search = groups.find(key); search != groups.end()) {
            State_group sg = search->second;
        } else {
            State_group sg;
            std::unordered_set<std::string> child_list;
            child_list.insert(key);
            sg.size = 1;
            sg.child_states = &child_list;
            groups.insert({key, sg});
            for(int i = 0; i < 4; i++) {
                //TODO
            }
        }
    }
    
    cout << groups.size();
}