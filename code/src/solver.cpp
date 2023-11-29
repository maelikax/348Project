/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * solver.cpp
 *   "Coordinator" of expression solving tasks, separate from the IO layer.
 *   Takes an std::string and attempts to tokenize it before passing it
 *   through the shunting yard algorithm and finally evaluating it to produce
 *   a resulting value.
 * 
 *   If any step of this process fails, a `parse_error` exception is thrown,
 *   which will propagate out to the caller (in this project, main.cpp) to be
 *   handled there.
 * 
 * Created:
 *   Adam Albee (2888458)
 *   29 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/

#include "solver.hpp"

// Public interface: just this function!
double ComputeExpression( string input ) {
    if ( input == "throw" ) {
        throw parse_error("example exception");
    }

    return -420.69;
}