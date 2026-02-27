#include "game.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
#include <vector>
//#include <memory>
#include <cmath>
using namespace std;
struct State_group
{
    std::unordered_set<std::string> child_states;
    std::unordered_set<std::string> connected_states;
    bool can_win = false;
    float eval = 0.0f;
};

struct directions{
    string right;
    string left;
    string up;
    string down;
};




void solve(State *state, std::unordered_map<string, directions>* game_states, std::unordered_map<string, State_group>* groups) {
    short x = state->size_x;
    short y = state->size_y;
    string sstr = string_from_state(state);
    std::unordered_set<std::string> seen_states{sstr};
    // groups
    State_group sg;
    std::unordered_set<std::string> connects;
    sg.connected_states = connects;
    std::unordered_set<std::string> childs;
    childs.insert(sstr);
    sg.child_states = childs;
    string sstr_no_player = remove_player_from_statestring(sstr);
    groups->insert({sstr_no_player, sg});
    
    stack<string> st;
    st.push(sstr);
    string current;
    while (!st.empty())
    {
        current = st.top();
        string current_no_player = remove_player_from_statestring(current);
        st.pop();
        directions dirs;
        game_states->insert({current, dirs});
        for (int i = 0; i < 4; i++)
        {
            auto it = groups->find(current_no_player);
            State_group& current_sg = it->second;
            State new_state = state_from_string(current, x, y);
            State* ptr = &new_state;
            attempt_move(ptr, (direction)i);
            std::string str = string_from_state(ptr);
            std::string str_no_player = remove_player_from_statestring(str);
            if (ptr->win) 
                current_sg.can_win = true;
            // Check groups
            if (auto search = groups->find(str_no_player); search != groups->end()) {
                // Group already exists
                State_group* sg1 = &search->second;
                if (sg1->can_win) current_sg.can_win = true;
                // Check if group already contains child state
                bool found = false;
                for (const std::string i : sg1->child_states)
                {
                    if (str.compare(i) == 0) {
                        found = true;
                    }
                    
                }
                if (!found) {
                    // If group does not contain child state we add it
                    sg1->child_states.insert(str);
                }
                
                if (current_no_player.compare(str_no_player) != 0) {
                    // If current and new does not belong to the same group, we add new to currents connections
                    if (!ptr->lost && !ptr->win) {
                        current_sg.connected_states.insert(str_no_player);
                    }
                }
            } else {
                // Group does not exist
                State_group sg2;
                sg2.connected_states = {};
                sg2.child_states = {str};
                sg2.can_win = ptr->win;

                if (!ptr->lost && !ptr->win) {
                    current_sg.connected_states.insert(str_no_player);
                }
                groups->insert({str_no_player, sg2});
            }
            if (!seen_states.count(str) && str != "LOST" && str != "WIN") {
                st.push(str);
            }
            seen_states.insert(str);
            switch (i)
            {
            case 0:
                game_states->find(current)->second.right = str;
                break;
            case 1:
                game_states->find(current)->second.left = str;
                break;
            case 2:
                game_states->find(current)->second.up = str;
                break;
            case 3:
                game_states->find(current)->second.down = str;
                break;
            default:
                break;
            }
        }
        
    }

    
    //merge_circular_dependencies(sstr_no_player, groups);    
}


bool recursive_find_gamestates(std::string state, std::unordered_set<string>* seen_states, std::unordered_map<string, State_group>* groups, short x, short y) {
    std::string state_no_player = remove_player_from_statestring(state);
    auto it = groups->find(state_no_player);
    State_group& current_sg = it->second;
    for (int i = 0; i < 4; i++){
        State st = state_from_string(state, x, y);
        State* ptr = &st;
        attempt_move(ptr, (direction)i);
        std::string str = string_from_state(ptr);
        std::string str_no_player = remove_player_from_statestring(str);
        if (ptr->win) 
            current_sg.can_win = true;

        // Check groups
        if (auto search = groups->find(str_no_player); search != groups->end()) {
            // Group already exists
            State_group* sg1 = &search->second;
            if (sg1->can_win) current_sg.can_win = true;
            // If group does not contain child state we add it
            sg1->child_states.insert(str);
            if (state_no_player.compare(str_no_player) != 0) {
                // If current and new does not belong to the same group, we add new to currents connections
                if (!ptr->lost && !ptr->win) {
                    current_sg.connected_states.insert(str_no_player);
                }
            }
        } else {
            // Group does not exist
            State_group sg2;
            sg2.connected_states = {};
            sg2.child_states = {str};
            sg2.can_win = ptr->win;

            if (!ptr->lost && !ptr->win) {
                current_sg.connected_states.insert(str_no_player);
            }
            groups->insert({str_no_player, sg2});
        }
        
        if (!seen_states->count(str) && str != "LOST" && str != "WIN") {
            seen_states->insert(str);
            bool win = recursive_find_gamestates(str, seen_states, groups, x, y);
            current_sg.can_win = win || current_sg.can_win;
        }
        
    }        
    return current_sg.can_win;
}

float recursive_find_entropies(std::string str, std::unordered_set<string>* seen_states, std::unordered_map<string, State_group>* groups) {
    if (str.compare("WIN") == 0) return 0.0f;
    else if (str.compare("LOST") == 0) return 999.0f;
    auto it = groups->find(str);
    State_group& current_sg = it->second;
    int win_count = 0;
    float min = 999;
    std::vector<float> entropies;
    for (std::string s : current_sg.connected_states) {
        
        auto inner = groups->find(s);
        State_group& inner_sg = inner->second;
        win_count += inner_sg.can_win;
        float entropy;
        if (!seen_states->count(s)) {
            seen_states->insert(s);
            entropy = recursive_find_entropies(s, seen_states, groups);
        }
        else {
            entropy = inner_sg.eval;
        }
        if (entropy < min) {
            min = entropy;
        }
    }
    float logval = log2f(current_sg.connected_states.size() - (win_count - 1));
    current_sg.eval = logval + min;
    return current_sg.eval;
}

float evaluate(State* state) {
    std::string str = string_from_state(state);
    std::string str_no_player = remove_player_from_statestring(str);
    State_group sg;
    sg.child_states.insert(str);
    std::unordered_set<string> seen_states = {str};
    std::unordered_map<string, State_group> groups = {{str_no_player, sg}};
    if (recursive_find_gamestates(str, &seen_states, &groups, state->size_x, state->size_y)) {
        std::unordered_set<string> seen_states2 = {str};
        sg.eval = recursive_find_entropies(str_no_player, &seen_states2, &groups);
    }
    else {
        cout << "Can not be won\n";
        return -1.0f;
    }
    for (const auto& n : groups) {
        for (const auto& m : n.second.connected_states) {
            if (n.first.compare(m) == 0) {
                cout << "WARNING: CIRCULAR DEPENDENCY DETECTED\n";
                cout << "circular:\n" << n.first << "\n" << m << "\n---\n";
            }
        }
    }
    return std::ceil(sg.eval * 100.0) / 100.0;
}
