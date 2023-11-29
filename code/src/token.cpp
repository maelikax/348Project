/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * token.cpp
 *   Implements a `Token_t` tagged-union (via Enum) type and a Tokenize function
 *   that takes in an std::string and outputs a std::queue<Token_t> representing
 *   the token stream for that input, throwing an error if an invalid character
 *   is found while parsing the string.
 * 
 * Created:
 *   Adam Albee (2888458)
 *   29 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/

#include "token.hpp"
using std::queue;
using std::string;

// TODO: check if manual memory management is necessary here
queue<Token_t> Tokenize( const string input ) {

    queue<Token_t> tokens;
    Token_t tok; // don't know how to make queue::emplace work with a tagged union

    size_t pos = 0;
    while ( pos < input.length() ) {
        tokens.push(tok);
        pos++;
    }

    return tokens;
}