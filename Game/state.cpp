#include <iostream>
#include <cassert>
#include <string>
using namespace std;
struct Position 
{
    short x;
    short y;
};
struct Cell
{
    short tile;
    short block;
    Position pos;
};
struct State {
    Cell** cells;
    short size_x;
    short size_y;
    Position player_pos;
    short* blocks;
    bool win;
    bool lost;
};
enum block{
    EMPTYBLOCK,
    PLAYER,
    RED,
    BLUE,
    GREEN,
    YELLOW
};
enum tile {
    EMPTYTILE,
    PLAYERGOAL,
    REDGOAL,
    BLUEGOAL,
    GREENGOAL,
    YELLOWGOAL,
    XTILE,
    PUSHRIGHT,
    PUSHLEFT,
    PUSHUP,
    PUSHDOWN
};
State empty_state(short x, short y) {
    State state;
    state.size_x = x;
    state.size_y = y;
    state.win = false;
    state.lost = false;

    state.cells = new Cell*[x];

    for (int i = 0; i < x; ++i) {
        Cell* c = new Cell[y];
        for (int j = 0; j < y; ++j)
        {
            c[j].pos.x = i;
            c[j].pos.y = j;
        }
        state.cells[i] = c;
    }
    return state;
}


State state_from_string(std::string s, short x, short y) {
    State state;
    state.size_x = x;
    state.size_y = y;
    state.win = false;
    state.lost = false;

    state.cells = new Cell*[x];
    assert(s.length() == x*y*2);

    short player_count = 0;
    for (int i = 0; i < x; ++i) {
        Cell* c = new Cell[y];
        for (int j = 0; j < y; ++j) {
            char c1 = s[(y*i*2)+(j*2)];
            char c2 = s[(y*i*2)+(j*2)+1];
            short s1 = c1 - '0';
            short s2 = c2 - '0';
            c[j].tile = s1;
            c[j].block = s2;
            c[j].pos.x = i;
            c[j].pos.y = j;
            if (s2 == PLAYER) {
                player_count++;
                state.player_pos.x = i;
                state.player_pos.y = j;
            }
        }
        state.cells[i] = c;
    }
    assert(player_count == 1);
    return state;
}


string string_from_state(State s) {
    char str[s.size_x*s.size_y*2]; 
    short count = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            str[count] = (char)s.cells[i][j].tile + '0';
            str[count+1] = (char)s.cells[i][j].block + '0';
            count+=2;
        }
    }
    return str;
}