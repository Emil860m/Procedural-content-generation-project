#include <iostream>
#include "../Game/solver.hpp"
#include <algorithm>
#include <random>
#include <cassert>
using namespace std;
struct Evaluated_state
{
    State state;
    float eval = 0.0f;
    /* data */
};
bool compareEval(const Evaluated_state &a, const Evaluated_state &b)
{
    return a.eval < b.eval;
}

Evaluated_state mutate(Evaluated_state estate) {
    return estate;
}

vector<Evaluated_state> selection(vector<Evaluated_state> population) {
    std::sort(population.begin(), population.end(), compareEval);
    vector<Evaluated_state> selected;
    int half = population.size() / 2;
    cout << half << "\n";/*
    for (int i = 0; i < population.size() - 1; i++) {
        selected.push_back(population[i % half]);
    }
    cout << selected.size();*/
    // keep simple? if so, sort then take top 1/3 and make full population
    return population;
}

Evaluated_state generate_level(short size_x, short size_y) {
    
    Evaluated_state es;
    State s = state_from_string("00000020000060606000006064600010656261600050406000", 5, 5);
    es.state = s;
    return es;
    /*
    int block_count = (rand() % 3) + 3;
    int special_tile_count = (rand() % 10); // TODO: change this so that the range is limited by the size

    // create empty state
    State s = empty_state(size_x, size_y);
    short x = size_x / 2;
    short y = size_y / 2;
    short counter = 0;
    // create island of tiles
    while (counter < (size_x * size_y) / 2) {
        if (s.cells[x][y].tile == EMPTYTILE) {
            counter++;
            s.cells[x][y].tile = TILE;
        }
        int randomNumber = rand() % 4;
        switch (randomNumber)
        {
            case 0:
                if (x < size_x - 1) {
                    x++;
                }
                break;
            case 1:
                if (x > 0) {
                    x--;
                }
                break;
            case 2:
                if (y < size_y - 1) {
                    y++;
                }
                break;
            case 3:
                if (y > 0) {
                    y--;
                }
                break;
            default:
                break;
        }
    }
    vector<pair<int,int>> tiles;
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            if (s.cells[i][j].tile == TILE) {
                tiles.push_back(pair<int,int>(i,j));
            }
        }
    }


    // add player block and hole

    random_device rd;
    mt19937 g(rd());
    shuffle(tiles.begin(), tiles.end(), g);
    // add other blocks and holes
    // (range 2-4 depending on x*y)
    cout << block_count << "\n";
    for (int i = 0; i < block_count; i++) {
        pair<int,int> tile = tiles[i];
        pair<int,int> block = tiles[i + block_count]; 
        s.cells[tile.first][tile.second].tile = i;
        s.cells[block.first][block.second].block = i;
    }

    // add special tiles
    // (range 0-10 depending on x*y)
    Evaluated_state es;
    es.state = s;
    return es;*/
}

Evaluated_state generate(short size_x, short size_y, short pop, short iter, short mut, short target) {
    vector<Evaluated_state> population;
    for (int i = 0; i < pop; i++)
    {
        population.push_back(generate_level(size_x, size_y));
    }
    Evaluated_state* best = &population[0];
    best->eval = evaluate(&population[0].state);
    for (Evaluated_state s : population) {
        cout << string_from_state(&s.state) << "\n";
        s.eval = evaluate(&s.state);
        if (best->eval < s.eval) {
            cout << "New best: " << s.eval << "\n";
            best = &s;
            cout << "Best is now: " << best->eval << "\n";
        }
    }
    cout << "Best so far: " << best->eval << "\n";
    for (int i = 0; i < 1; i++) {
        cout << i << "\n";
        vector<Evaluated_state> selected = selection(population);
        vector<Evaluated_state> next_iter;
        next_iter.push_back(*best);
        assert(pop == population.size());
        for (Evaluated_state es : population) {
            next_iter.push_back(mutate(es));
        }
        // for population
            // mutate
            // append mutation to next_iter
        
        population = next_iter;
        for (Evaluated_state s : population) {
            s.eval = evaluate(&s.state);
            if (best->eval < s.eval) {
                best = &s;
            }
        }
        // population = next_iter
        // evaluate new population and check if new best

        // if close enough to or over target, return best
        if (best->eval > target) return *best;
    }
    return *best;
}

