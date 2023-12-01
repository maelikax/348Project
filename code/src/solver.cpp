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
#include "token.hpp"
using std::string;
using std::queue;

#include "shunyard.hpp"
#include "rpn.hpp"

// // print token list, for debugging:
// #include <iostream>
// using std::cout;
// using std::endl;

// static void printTokenList( queue<Token_t> tokens) {
//     while ( !tokens.empty() ) {
//         auto tok = tokens.front();
//         tokens.pop();

//         switch ( tok.type ) {
//             case TokenType::Number: {
//                 cout << tok.value;
//             } break;
//             case TokenType::Operator: {
//                 switch ( tok.op ) {
//                     case Operator::Add: {
//                         cout << '+';
//                     } break;
//                     case Operator::Pos: {
//                         cout << '@';
//                     } break;
//                     case Operator::Sub: {
//                         cout << '-';
//                     } break;
//                     case Operator::Neg: {
//                         cout << '~';
//                     } break;
//                     case Operator::Mul: {
//                         cout << '*';
//                     } break;
//                     case Operator::Div: {
//                         cout << '/';
//                     } break;
//                     case Operator::Mod: {
//                         cout << '%';
//                     } break;
//                     case Operator::Exp: {
//                         cout << '^';
//                     } break;
//                 }
//             } break;
//             case TokenType::OpenBracket: {
//                 cout << (tok.bracket == BracketType::Paren ? '(' : '[');
//             } break;
//             case TokenType::CloseBracket: {
//                 cout << (tok.bracket == BracketType::Paren ? ')' : ']');
//             } break;
//         }
//         cout << ',';
//     }
//     cout << endl;
// }

// Public interface: just this function!
double ComputeExpression( string input ) {
    queue<Token_t> tokens = Tokenize(input);
    // printTokenList(tokens);
    tokens = shunyard(tokens);
    // printTokenList(tokens);
    return evalrpn(tokens);
}
