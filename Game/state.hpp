#include <string>
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

State empty_state(short x, short y);

State state_from_string(std::string s, short x, short y);

std::string string_from_state(State s);