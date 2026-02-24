#include <iostream>
#include "../Game/solver.hpp"
using namespace std;
struct Evaluated_state
{
    State state;
    float eval = 0.0f;
    /* data */
};


State generate(short size_x, short size_y) {
    Evaluated_state es;
    State s = empty_state(size_x, size_y);
    es.state = s;
    es.eval = evaluate(&s);
    cout << es.eval << "\n";
    return s;
}