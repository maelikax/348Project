/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * rpn.cpp
 *   Evaluates ("Solves") a mathematical expression in the form of an std::queue<Token_t>
 *   stream formatted in postfix (aka Reverse Polish) notation
 * 
 * Created:
 *   Adam Albee (2888458)
 *   30 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   30 November 2023
 *****/

#include "rpn.hpp"
using std::queue;
// using Token_t; + associated enums
#include "solver.hpp"
// using parse_error;
#include <stack>
using std::stack;
#include <cmath>
using std::fmod;
using std::pow;
using std::isnan;

double evalrpn( std::queue<Token_t> tokens ) {
    stack<double> nums;
    while ( !tokens.empty() ) {
        Token_t op = tokens.front();
        tokens.pop();

        if ( op.type == TokenType::Number ) {
            nums.push( op.value );
        } else { // is an operator
            // unary ops
            if ( op.op == Operator::Pos ) { continue; }
            if ( op.op == Operator::Neg ) {
                if ( nums.empty() ) { throw parse_error("Missing Operands"); }
                // TODO: check if this can modify in-place
                double n = nums.top();
                nums.pop();
                nums.push(-n);
                continue;
            }
            // binary ops
            if ( nums.size() < 2 ) { throw parse_error("Missing Operands"); }
            double b = nums.top();
            nums.pop();
            double a = nums.top();
            nums.pop();
            double res;

            switch (op.op) {
                case Operator::Pos:
                case Operator::Neg: continue; // Neg and Pos already handled!

                case Operator::Add: {
                    res = a + b;
                    if ( isnan(res) ) {
                        if ( a > b ) {
                            throw parse_error("Undefined Operation: +Infinity + -Infinity");
                        } else {
                            throw parse_error("Undefined Operation: -Infinity + +Infinity");
                        }
                    }
                } break;

                case Operator::Sub: {
                    res = a - b;
                    if ( isnan(res) ) {
                        if ( a > 0 ) {
                            throw parse_error("Undefined Operation: +Infinity - +Infinity");
                        } else {
                            throw parse_error("Undefined Opeartion: -Infinite - -Infinity");
                        }
                    }
                } break;

                case Operator::Mul: {
                    res = a * b;
                    if ( isnan(res) ) { throw parse_error("Undefined Operation: Infinity * 0"); }
                } break;

                case Operator::Div: {
                    if ( b == 0 ) { throw parse_error("Undefined Operation: Division by Zero"); }
                    res = a / b;
                } break;

                case Operator::Mod: {
                    res = fmod(a, b);
                } break;

                case Operator::Exp: {
                    if ( a == 0 && b == 0 ) { throw parse_error("Undefined Operation: 0^0"); }
                    res = pow(a, b);
                    if ( isnan(res) ) { throw parse_error("Undefined Operation: Even Root of Negative Value"); }
                } break;
            }

            nums.push(res);
        }
    }

    if ( nums.empty() ) { throw parse_error("Missing Operands"); }
    if ( nums.size() != 1 ) { throw parse_error("Missing Operators"); }

    return nums.top();
}