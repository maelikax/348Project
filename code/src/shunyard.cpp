/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * shunyard.cpp
 *   Implementation of Djikstra's Shunting Yard algorithm to reorganize the
 *   infix-formatted input token stream into a postfix (aka Reverse Polish Notation)
 *   output token stream, both streams of the form std::queue<Token_t>
 * 
 * Created:
 *   Mahgoub Husien
 *   27 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   30 November 2023
 *****/

#include "shunyard.hpp"
using std::queue;
// using Token_t; + associated enums

#include "solver.hpp"
// using parse_error;
#include <stack>
using std::stack;
#include <map>
using std::map;
#include <cmath>
// using pow;


static map<Operator,bool> isLeftAssociatve = {
    {Operator::Add, true},
    {Operator::Pos, false},
    {Operator::Sub, true},
    {Operator::Neg, false},
    {Operator::Mul, true},
    {Operator::Div, true},
    {Operator::Mod, true},
    {Operator::Exp, false}
};

// larger number = higher precedence
static map<Operator,int> precedence = {
    {Operator::Add, 1},
    {Operator::Sub, 1},
    {Operator::Mul, 2},
    {Operator::Div, 2},
    {Operator::Mod, 2},
    {Operator::Pos, 3},
    {Operator::Neg, 3},
    {Operator::Exp, 3} 
};


// TODO: memory management concerns:
//       pass `tokens` by const reference + iterate instead of `pop`?
//       pre-allocate `output` size and/or reuse input queue?
queue<Token_t> shunyard( queue<Token_t> tokens ) {
    queue<Token_t> output;
    stack<Token_t> opStack;

    bool lastTokenWasOpenBracket = false;
    while ( !tokens.empty() ) {
        Token_t tok = tokens.front();
        tokens.pop();

        switch ( tok.type ) {
            case TokenType::Number: {
                lastTokenWasOpenBracket = false;
                output.push(tok);
            } break;

            case TokenType::OpenBracket: {
                lastTokenWasOpenBracket = true;
                opStack.push(tok);
            } break;

            case TokenType::CloseBracket: {
                if ( lastTokenWasOpenBracket ) { throw parse_error("Bracketed Subexpression is Empty"); }
                // NOTE: should mismatched/unbalanced bracket have a higher error priority than empty contents?
                lastTokenWasOpenBracket = false;
                bool matched = false;

                // move operators from the stack to the output, until a matching open bracket is found or the stack underflows
                while ( !opStack.empty() ) {
                    Token_t op = opStack.top();
                    opStack.pop();
                    if ( op.type == TokenType::OpenBracket ) {
                        // tried to match a square bracket and parenthesis
                        if ( op.bracket != tok.bracket ) { throw parse_error("Mismatched Bracket Types"); }
                        matched = true;
                        break;
                    } else {
                        output.push(op);
                    }
                }
                if ( !matched ) { throw parse_error("Unbalanced Brackets"); }
            } break;

            case TokenType::Operator: {
                lastTokenWasOpenBracket = false;
                for (;;) {
                    if ( opStack.empty() ) { break; }
                    Token_t op = opStack.top();
                    if ( op.type == TokenType::OpenBracket ) { break; }
                    if ( precedence[op.op] > precedence[tok.op] || (precedence[op.op] == precedence[tok.op] && isLeftAssociatve[tok.op]) ) {
                        opStack.pop();
                        output.push(op);
                        continue;
                    }
                    break;
                }
                opStack.push(tok);
            } break;
        }
    }

    // all tokens have been parsed, pop opStack to output:
    while ( !opStack.empty() ) {
        Token_t op = opStack.top();
        opStack.pop();
        if ( op.type == TokenType::OpenBracket ) { throw parse_error("Unbalanced Brackets"); }
        output.push(op);
    }

    return output;
}