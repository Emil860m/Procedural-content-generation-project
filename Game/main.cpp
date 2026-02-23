#include <iostream>
#include <unordered_map>
#include "solver.hpp"
using namespace std;

int main() {
    string str = "00000020000060606000006064600010656261600050406000";
    State state = state_from_string(str, 5, 5);
    State *ptr = &state;
    //cout << str + "\n";
    std::unordered_map<string, directions> game_states = {};
    std::unordered_map<string, State_group> groups = {};
    groups.reserve(10000000);
    solve(ptr, &game_states, &groups);
    

    //if (auto search = groups.find("00000020000060606000006064600010656260600050406000"); search != groups.end()) {
     //   cout << search->second[0].child_states.size();
        //cout << search->second[0].child_states.size() <<  "\n" << search->second[0].can_win << "\n" << search->second[0].connections<< "\n";
    //}
    
    for (const auto& n : groups) {
        cout << n.first << " " << n.second.child_states.size() << "\n";
        /*for (std::string s : n.second.connected_states) {
            cout << s << "\n";
        }*/
    }
    for (const std::pair<const string, directions>& n : game_states) {
        //cout << n.first << " " << n.second.down << "\n";
    }
    //cout << game_states.size();
    cout << &groups.begin()->second << endl;

    //group_gamestates(&game_states);
    return 0;
}
