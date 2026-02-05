#include <iostream>
#include <string>
#include "state.hpp"
using namespace std;

int main() {
    State s = empty_state(3,4);
    State s2 = state_from_string("123456789011", 2, 3);
    string str = string_from_state(s2);
    cout << str;
        cout << "\n";
        cout << "\n";
        cout << "\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            Cell c = s2.cells[i][j];
            cout << c.pos.x;
            cout << c.pos.y;
            cout << c.tile;
            cout << c.block;
            cout << "\n";
        }
    }
    cout << "Hello World!";
    return 0;
} 