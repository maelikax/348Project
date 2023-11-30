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
#include "solver.hpp"
// using parse_error;
#include <ctype.h>
// using isspace;
// using isdigit;
#include <sstream>
using std::stringstream;

// TODO: check if manual memory management is necessary/helpful here
queue<Token_t> Tokenize( const string input ) {
// throw parse_error("example exception");
    queue<Token_t> tokens;
    Token_t tok; // don't know how to make queue::emplace work with a tagged union

    size_t pos = 0;
    while ( pos < input.length() ) {

        // NOTE: this tokenization setup is somewhat inefficient and will not extend easily to more complex grammars.
        //       but, for this project, it is more than sufficient.
        switch ( input[pos] ) {
            // BRACKETS
            case '(': {
                tok.type = TokenType::OpenBracket;
                tok.bracket = BracketType::Paren;
            } break;

            case '[': {
                tok.type = TokenType::OpenBracket;
                tok.bracket = BracketType::Square;
            } break;

            case ')': {
                tok.type = TokenType::CloseBracket;
                tok.bracket = BracketType::Paren;
            } break;

            case ']': {
                tok.type = TokenType::CloseBracket;
                tok.bracket = BracketType::Square;
            } break;


            // OPERATORS
            case '+': { // handles binary Add, discards unary Pos (since it is effectively a no-op in this grammar)
                tok.type = TokenType::Operator;
                tok.op = Operator::Add;
                // discard unary Positive:
                if ( tokens.empty() ) {
                    pos++;
                    continue;
                } else {
                    Token_t prev = tokens.back();
                    if ( prev.type == TokenType::Operator || prev.type == TokenType::OpenBracket ) {
                        pos++;
                        continue;
                    }
                }
            } break;

            case '-': { // handles binary Sub && unary Neg
                tok.type = TokenType::Operator;
                tok.op = Operator::Sub;
                // check if unary Negation instead:
                if ( tokens.empty() ) {
                    tok.op = Operator::Neg;
                    break;
                } else {
                    Token_t prev = tokens.back();
                    if ( prev.type == TokenType::Operator || prev.type == TokenType::OpenBracket ) {
                        tok.op = Operator::Neg;
                        break;
                    }
                }
            } break;
            // NOTE: adjacent '+' and '-', ignoring whitespace, are treated as unary operations!
            //       e.g. "5-- -  +   -     1" ==> "5 Sub Neg Neg Neg 1"
            //       It's not clear if this is desired or intended behavior from the current specs.

            case '*': { // handles "*" -> Mul and "**" -> Exp
                tok.type = TokenType::Operator;
                if ( pos + 1 < input.length() && input[pos+1] == '*' ) {
                    pos++;
                    tok.op = Operator::Exp;
                } else {
                    tok.op = Operator::Mul;
                }
            } break;

            case '/': {
                tok.type = TokenType::Operator;
                tok.op = Operator::Div;
            } break;

            case '^': {
                tok.type = TokenType::Operator;
                tok.op = Operator::Exp;
            } break;

            case '%': {
                tok.type = TokenType::Operator;
                tok.op = Operator::Mod;
            } break;


            default: {
                char ch = input[pos];

                // IGNORE WHITESPACE
                if ( isspace(ch) ) {
                    pos++;
                    continue;
                }

                // NUMBER CONSTANTS
                // NOTE: check if the locale affects number parsing (!!)
                // TODO: reuse the memory here for efficiency when parsing multiple numbers?
                // NOTE: should number constants be allowed to start and end with separator characters?

                // This is the most complex part of the tokenizer!
                // - all values are read as doubles
                // - '_' and ',' can be used as digit separators and are completely ignored as part of number constants
                // - '.' is used as the decimal separator, only 0 or 1 is allowed per number
                // - Scientific notation is supported!
                //     - <digits>(.<digits>)?[eE]([+-]?)<digits>
                // - no spaces allowed inside number constants!
                // - + or - only valid after 'e'/'E' character
                // - some digits must be present either before or after the decimal '.', but both is not required
                //     - e.g. "0.1", "1.", and ".2" are all valid
                // - the exponent must be an integer, if present
                // - if the 'e' character is present, the exponent must also be present
                if ( isdigit(ch) || ch == '_' || ch == ',' || ch == '.' ) {
                    tok.type = TokenType::Number;

                    stringstream numStr;
                    bool hasDigits = false;
                    bool decimalUsed = false;
                    bool inExponent = false;
                    for( ; pos < input.length(); ch = input[++pos] ) {
                        if ( isdigit(ch) ) {
                            hasDigits = true;
                            numStr << ch;
                            continue;
                        }
                        if ( ch == '_' || ch == ',' ) { continue; } // ignore separator characters
                        if ( ch == 'e' || ch == 'E' ) {
                            if ( inExponent ) { throw parse_error("Invalid Numeric Constant: scientific notation invalid exponent"); } 
                            if ( !hasDigits ) { throw parse_error("Invalid Numeric Constant: scientific notation missing mantissa"); }
                            decimalUsed = true; // no decimal allowed in exponent
                            hasDigits = false; // exponent must have its own digits
                            inExponent = true;
                            numStr << ch;
                            if ( input[pos+1] == '+' || input[pos+1] == '-' ) {
                                pos++;
                                numStr << input[pos+1];
                            }
                            continue;
                        }
                        if ( ch == '.' ) {
                            if ( decimalUsed ) {
                                if ( inExponent ) {
                                    throw parse_error("Invalid Numeric Constant: scientific notation invalid exponent");
                                } else {
                                    throw parse_error("Invalid Numeric Constant: decimal used more than once");
                                }
                            }
                            decimalUsed = true;
                            numStr << ch;
                            continue;
                        }

                        // not a digit, separator, decimal, or `e`, we're done parsing this number!
                        if ( !hasDigits ) {
                            if ( inExponent ) {
                                throw parse_error("Invalid Numeric Constant: scientific notation invalid exponent");
                            } else {
                                throw parse_error("Invalid Numeric Constant: number contains no digits");
                                // TODO: specific error messages for weird digit separator use? Currently they are ignored entirely!
                            }
                        }
                        break;
                    }

                    numStr >> tok.value;
                    pos--; // reparse this character, as it isn't part of this token
                    break;
                }

                // INVALID CHARACTERS
                throw parse_error("Invalid Character in Expression");
            }
        }

        tokens.push(tok);
        pos++;
    }

    return tokens;
}