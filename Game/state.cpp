#include <iostream>
#include <cassert>
#include <string>
#include <vector>
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
    std::vector<std::vector<Cell>> cells;
    //Cell** cells;
    short size_x;
    short size_y;
    Position player_pos;
    short block_count;
    bool win;
    bool lost;

    ~State() {
        if (cells) {
            for (int i = 0; i < size_x; i++)
                delete[] cells[i];
            delete[] cells;
        }
    }

    State(const State& other) {
        size_x = other.size_x;
        size_y = other.size_y;
        player_pos = other.player_pos;
        block_count = other.block_count;
        win = other.win;
        lost = other.lost;

        cells = new Cell*[size_x];
        for (int i = 0; i < size_x; i++) {
            cells[i] = new Cell[size_y];
            for (int j = 0; j < size_y; j++)
                cells[i][j] = other.cells[i][j];
        }
    }

    State& operator=(const State& other) {
        if (this == &other) return *this;

        this->~State();

        size_x = other.size_x;
        size_y = other.size_y;
        player_pos = other.player_pos;
        block_count = other.block_count;
        win = other.win;
        lost = other.lost;

        cells = new Cell*[size_x];
        for (int i = 0; i < size_x; i++) {
            cells[i] = new Cell[size_y];
            for (int j = 0; j < size_y; j++)
                cells[i][j] = other.cells[i][j];
        }

        return *this;
    }
    State() : cells(nullptr), size_x(0), size_y(0), block_count(0), win(false), lost(false) {}
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
    TILE,
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
    short blocks[4];

    short player_count = 0;
    short block_count = 0;
    for (int i = 0; i < x; ++i) {
        Cell* c = new Cell[y];
        for (int j = 0; j < y; j++) {
            char c1 = s[(((y*i)+j)*2)];
            char c2 = s[(((y*i)+j)*2)+1];
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
            else if (s2 > PLAYER && s2 <= YELLOW) {
                for(int k = 0; k < block_count; k++) {
                    assert(blocks[k] != s2);
                }
                blocks[block_count] = s2;
                block_count ++;
            }
        }
        state.cells[i] = c;
    }
    state.block_count = block_count;
    assert(player_count == 1);
    return state;
}


string string_from_state(State *s) {
    if (s->win) return "WIN";
    else if (s->lost) return "LOST";
    string str = "";
    short count = 0;
    for (int i = 0; i < s->size_x; ++i) {
        for (int j = 0; j < s->size_y; ++j) {
            str += char(s->cells[i][j].tile + '0');
            str += char(s->cells[i][j].block + '0');

            count+=2;
        }
    }
    return str;
}


void deep_copy(State *dst, const State *src) {
    dst->block_count = src->block_count;
    dst->size_x = src->size_x;
    dst->size_y = src->size_y;
    dst->win = src->win;
    dst->player_pos = src->player_pos;
    dst->lost = src->lost;
    dst->cells = new Cell*[dst->size_x];
    for(int i = 0; i < dst->size_x; i++) {
        Cell* c = new Cell[dst->size_y];
        for (int j = 0; j < dst->size_y; j++)
        {
            c[j] = src->cells[i][j];
        }
        dst->cells[i] = c;
        
    }
}

string remove_player_from_statestring(string s) {
    for (int i = 0; i < s.size(); i+=2) {
        if (s[i + 1] == '1') {
            s.replace(i+1, 1, "0");
        }
    }
    return s;
}