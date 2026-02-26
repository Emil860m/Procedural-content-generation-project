#include <iostream>
#include "../Game/solver.hpp"
#include <algorithm>
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

Evaluated_state generate(short size_x, short size_y, short pop, short iter, short mut, short target) {
    vector<Evaluated_state> population;
    for (int i = 0; i < pop; i++)
    {
        population.push_back(generate_level());
    }
    Evaluated_state* best = &population[0];
    best->eval = evaluate(&population[0].state);
    for (Evaluated_state s : population) {
        s.eval = evaluate(&population[0].state);
        if (best->eval < s.eval) {
            best = &s;
        }
    }
    for (int i = 0; i < iter; i++) {
        vector<Evaluated_state> selected = selection(population);
        vector<Evaluated_state> next_iter;
        next_iter.push_back(*best);

        // for population
            // mutate
            // append mutation to next_iter
        
        // population = next_iter
        // evaluate new population and check if new best

        // if close enough to or over target, return best
        
    }
    //std::sort(population.begin(), population.end(), compareEval);
    return *best;
}

Evaluated_state mutate(Evaluated_state estate) {

}

vector<Evaluated_state> selection(vector<Evaluated_state> population) {
    // keep simple? if so, sort then take top 1/3 and make full population

}

Evaluated_state generate_level(short size_x, short size_y) {
    // create empty state

    // create island of tiles

    // add player block and hole

    // add other blocks and holes
    // (range 2-5 depending on x*y)

    // add special tiles
    // (range 0-10 depending on x*y)
}