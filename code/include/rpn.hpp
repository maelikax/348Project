/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * rpn.hpp
 *   see rpn.cpp for details
 * 
 * Created:
 *   Adam Albee (2888458)
 *   30 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   30 November 2023
 *****/

#ifndef RPN_HPP
#define RPN_HPP

#include "token.hpp"
#include <queue>

double evalrpn( std::queue<Token_t> );

#endif // RPN_HPP