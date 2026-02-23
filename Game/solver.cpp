#include "game.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
#include <vector>
#include <memory>
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
    //sg.connections = 0;
    std::unordered_set<std::string> childs;
    childs.insert(sstr);
    sg.child_states = childs;
    //sg.size = 1;
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
                    //sg1->size++;
                }
                
                if (current_no_player.compare(str_no_player) != 0) {
                    // If current and new does not belong to the same group, we add new to currents connections
                    if (!ptr->lost && !ptr->win) {
                        current_sg.connected_states.insert(str_no_player);
                        //current_sg.connections++;
                    }
                }
            } else {
                // Group does not exist
                State_group sg2;
                sg2.connected_states = {};
                //sg2.connections = 0;
                sg2.child_states = {str};
                //sg2.size = 1;
                sg2.can_win = ptr->win;

                if (!ptr->lost && !ptr->win) {
                    current_sg.connected_states.insert(str_no_player);
                    //current_sg.connections++;
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

void merge_circular_dependencies(std::string start, std::unordered_map<string, State_group>* groups) {
    if (auto search = groups->find(start); search != groups->end()) {
        State_group* sg = &search->second;
        for (string s : sg->connected_states) {
            bool circular = false;
            if (auto search2 = groups->find(s); search2 != groups->end()) {
                State_group* sg_connected = &search2->second;
                for (string connected : sg_connected->connected_states) {
                    if (s.compare(connected) == 0) {
                        circular = true;
                        break;
                    }
                }
                if (circular) {
                    
                }
            }
        }
    }
}


bool group_gamestates(std::string start_group, std::unordered_map<string, State_group>* groups) {
    if (start_group == "WIN")
        return true;
    else if (start_group == "LOST")
        return false;

    return false;

    
}

/*
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
}*/