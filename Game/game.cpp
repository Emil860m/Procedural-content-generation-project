#include "state.hpp"
#include <cassert>
#include <iostream>
using namespace std;



void move(State *current_state, direction dir, Position block_pos) {
    assert(dir <= 3);
    Position new_pos;
    new_pos.x = block_pos.x;
    new_pos.y = block_pos.y;
    if (dir == RIGHT) {
        new_pos.x += 1;
    } else if(dir == LEFT) {
        new_pos.x -= 1;
    } else if(dir == UP) {
        new_pos.y -= 1;
    } else if(dir == DOWN) {
        new_pos.y += 1;
    }

    // THE MOVE ITSELF
    current_state->cells[new_pos.x][new_pos.y].block = current_state->cells[block_pos.x][block_pos.y].block;
    current_state->cells[block_pos.x][block_pos.y].block = EMPTYBLOCK;

    // PLAYER POS CHECK
    if (current_state->cells[new_pos.x][new_pos.y].block == PLAYER)
    {
        current_state->player_pos = new_pos;
        // XTILE CHECK
        if (current_state->cells[block_pos.x][block_pos.y].tile == XTILE)  {
            current_state->cells[block_pos.x][block_pos.y].tile = 0;
        }
        // PLAYER WIN CHECK
        if (current_state->cells[new_pos.x][new_pos.y].tile == PLAYER) {
            if (current_state->block_count == 0) current_state->win = true;
            else current_state->lost = true;
        }
    }

    // BLOCK IN HOLE CHECK
    short tile = current_state->cells[new_pos.x][new_pos.y].tile;
    if (0 < tile && tile < 6) {
        if (current_state->cells[new_pos.x][new_pos.y].block == tile) {
            current_state->block_count--;
            current_state->cells[new_pos.x][new_pos.y].block = EMPTYBLOCK;
            current_state->cells[new_pos.x][new_pos.y].tile = TILE;
        }
        else {
            current_state->lost = true;
        }
    }


    // PUSH BLOCK CHECK
    // TODO
}

bool is_move_legal(State *current_state, direction dir, Position block_pos) {
    assert(dir <= 3);
    Position new_pos;
    new_pos.x = block_pos.x;
    new_pos.y = block_pos.y;
    if (dir == RIGHT) {
        new_pos.x += 1;
    } else if(dir == LEFT) {
        new_pos.x -= 1;
    } else if(dir == UP) {
        new_pos.y -= 1;
    } else if(dir == DOWN) {
        new_pos.y += 1;
    }
    if (!(0 <= new_pos.x && new_pos.x < current_state->size_x)) {
        return false;
    }
    else if (!(0 <= new_pos.y && new_pos.y < current_state->size_y)) {
        return false;
    }
    else if (current_state->cells[new_pos.x][new_pos.y].tile == 0) {
        return false;
    }
    else if (current_state->cells[new_pos.x][new_pos.y].block != 0) {
        if (is_move_legal(current_state, dir, new_pos)) {
            move(current_state, dir, block_pos);
            return true;
        }
        return false;
    }
    move(current_state, dir, block_pos);
    return true;
}


void attempt_move(State *current_state, direction dir) {
    is_move_legal(current_state, dir, current_state->player_pos);
}