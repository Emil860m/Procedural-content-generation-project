#include "game.hpp"
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cstring>
#include <vector>
using namespace std;
struct State_group
{
    std::vector<std::string> child_states;
    std::vector<State_group*> connected_states;
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

    // groups
    std::unordered_map<string, State_group*> groups = {};
    State_group sg;
    std::vector<State_group*> connects;
    sg.connected_states = connects;
    sg.connections = 0;
    std::vector<std::string> childs;
    childs.push_back(sstr);
    sg.child_states = childs;
    sg.size = 1;
    string sstr_no_player = remove_player_from_statestring(sstr);
    groups.insert({sstr_no_player, &sg});
    
    stack<string> st;
    st.push(sstr);
    string current;
    while (!st.empty())
    {
        current = st.top();
        string current_no_player = remove_player_from_statestring(current);
        State_group *current_sg = groups.find(current_no_player)->second;
        st.pop();
        directions dirs;
        game_states[0].insert({current, dirs});
        for (int i = 0; i < 4; i++)
        {
            State new_state = state_from_string(current, x, y);
            State* ptr = &new_state;
            attempt_move(ptr, (direction)i);
            std::string str = string_from_state(ptr);
            std::string str_no_player = remove_player_from_statestring(str);

            // Check groups
            if (auto search = groups.find(str_no_player); search != groups.end()) {
                // Group already exists
                State_group* sg1 = search->second;
                // Check if group already contains child state
                bool found = false;
                for (const std::string i : sg1[0].child_states)
                {
                    if (str.compare(i) == 0) {
                        found = true;
                    }
                }
                if (!found) {
                    // If group does not contain child state we add it
                    sg1[0].child_states.push_back(str);
                    sg1[0].size++;
                }
                
                if (current_no_player.compare(str_no_player) != 0) {
                    cout << current_no_player << "\n" << str_no_player << "\n----\n";
                    // If current and new does not belong to the same group, we add new to currents connections
                    if (str != "LOST" && str != "WIN") {
                        current_sg[0].connected_states.push_back(sg1);
                        current_sg[0].connections++;
                    }
                }
            } else {
                // Group does not exist
                State_group* sg1;
                std::vector<State_group*> connects;
                sg1[0].connected_states = connects;
                sg1[0].connections = 0;
                std::vector<std::string> child_list;
                child_list.push_back(str);
                sg1[0].child_states = child_list;
                sg1[0].size = 1;
                groups.insert({str_no_player, sg1});
                current_sg[0].connected_states.push_back(sg1);
                current_sg[0].connections++;
                //cout << current_sg[0].connections;
            }
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

    if (auto search = groups.find("00000020000060606000006064600010656260600050406000"); search != groups.end()) {
        cout << search->second[0].size <<  "\n" << groups.size() << "\n" << search->second[0].connections<< "\n";

    }
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