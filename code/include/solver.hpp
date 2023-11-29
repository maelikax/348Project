/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * solver.hpp
 *   see solver.cpp for details
 * 
 * Created:
 *   Adam Albee (2888458)
 *   18 September 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>

// TODO: move this into its own `parse_error.h` file?
#include <stdexcept>
// Copy + Expose public interface of `std::runtime_error`, for the `.what()` method
// Done this way since we want a custom error type but really only need a custom name.
// TODO: use subtypes for each component to more easily distinguish them?
struct parse_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

// ComputeExpression will throw an above `parse_error` exception for any error
// state caused by invalid expressions. Any other kind of exception is due to
// mistakes or bugs in the code!
double ComputeExpression( std::string input );

#endif // SOLVER_HPP