#include "game.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
using namespace std;
struct State_group
{
    State* child_states;
    State* connected_states;
    bool can_win;
    float eval;
};

struct directions{
    string right;
    string left;
    string up;
    string down;
};




void solve(State *state) {
    short x = state->size_x;
    short y = state->size_y;
    string sstr = string_from_state(state);
    std::unordered_set<std::string> seen_states{sstr};
    std::unordered_map<string, directions> game_states = {};
    directions d;
    game_states.insert({sstr, d}); 
    stack<string> st;
    st.push(sstr);
    string current;
    while (!st.empty())
    {
        current = st.top();
        st.pop();
        directions dirs;
        game_states.insert({current, dirs});
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
                game_states.find(current)->second.right = str;
                break;
            case 1:
                game_states.find(current)->second.left = str;
                break;
            case 2:
                game_states.find(current)->second.up = str;
                break;
            case 3:
                game_states.find(current)->second.down = str;
                break;
            default:
                break;
            }
        }
        
    }
    cout << seen_states.size() << "\n" << game_states.size() << "\n";
    if (auto search = game_states.find("00000060000060606000006060600010616060600060600000"); search != game_states.end())
        std::cout << "Found " << search->first << ' ' << search->second.up << '\n';
    else
        std::cout << "Not found\n";
    
}