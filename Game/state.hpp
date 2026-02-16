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
    short block_count;
    bool win;
    bool lost;
};
enum direction {
    RIGHT,
    LEFT,
    UP,
    DOWN
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

State empty_state(short x, short y);

State state_from_string(std::string s, short x, short y);

std::string string_from_state(State *s);

void deep_copy(State *dst, const State *src);

string remove_player_from_statestring(string s);