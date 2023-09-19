// ** TODO: prologue header
#ifndef SOLVER_H
#define SOLVER_H

#include <string>
using std::string;

#include <exception>
using std::invalid_argument;

double ComputeExpression( string input ) {
    if ( input == "throw" ) {
        throw invalid_argument("example exception");
    }

    return -420.69;
}

#endif // SOLVER_H