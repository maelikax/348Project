/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * token.hpp
 *   see token.cpp for details
 * 
 * Created:
 *   Adam Albee (2888458)
 *   18 September 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/

#include <string>
#include <queue>

enum class TokenType   { Number, OpenBracket, CloseBracket, Operator };
enum class Operator    { Add, Sub, Neg, Mul, Div, Mod, Exp };
enum class BracketType { Square, Paren };

struct Token_t {
    TokenType type;
    union {
        Operator    op;
        BracketType bracket;
        double      value;
    };
};

std::queue<Token_t> Tokenize( std::string input );