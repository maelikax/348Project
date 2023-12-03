/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * main.cpp
 *   expression REPL, with handling for CRLF and LF
 *   line endings, and stdin and stdout re-routing.
 * 
 *   Uses exceptions to handle invalid expressions,
 *   specifically of the `invalid_argument` type.
 * 
 * Created:
 *   Adam Albee (2888458)
 *   18 September 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::getline;

#include <string>
using std::string;

#include <unistd.h>
// using isatty;

#include "solver.hpp"
// using parse_error, ComputeExpression

#include "tests.hpp"

int main() {
    // uncommet function below - runs test cases
    // runTests();

    // first line is empty to look pretty
    cout << "                                                  \n"
         << "              ==== TEAM ORANGE ====               \n"
         << "                Expression Solver                 \n"
         << "              ====    =====    ====               \n"
         << "                                                  \n"
         << "Please enter equations using only these operators:\n"
         << " - addition (a + b)                               \n"
         << " - unary positive (+a)                            \n"
         << " - subtraction (a - b)                            \n"
         << " - unary negation (-a)                            \n"
         << " - multiplication (a * b)                         \n"
         << " - division (a / b)                               \n"
         << " - exponentiation (a ^ b or a ** b)               \n"
         << "                                                  \n"
         << "For precedence handling, both parentheses `()` and\n"
         << "square brackets `[]` are supported!               \n"
         << "                                                  \n"
         << "To exit the program, enter 'quit' or use Ctrl+D.  \n"
         << "                                                  \n"
         << "              ====    =====    ====               \n"
         << endl; // additional newline + flushes stdout

    string input;
    double result;

    while ( !cin.eof() ) { // close program if stdin is closed
        input.clear();
        // write prompt only to terminal
        if ( isatty(STDOUT_FILENO) ) {
            cout << "$> ";
        }
        getline(cin, input);

        // don't process empty lines:
        if ( input.length() == 0 || input == "\r" ) {
            // erase prompt on terminal stdout:
            if ( isatty(STDOUT_FILENO) ) {
                cout << "\r";
            }
            continue;
        }

        // remove CR from CRLF line endings
        if ( input.back() == '\r' ) {
            input.pop_back();
        }

        // echo input + prompt if not *writing* to a terminal
        if ( !isatty(STDOUT_FILENO) ) {
            cout << "$> " << input << endl;

        // echo input if not reading from a terminal
        } else if ( !isatty(STDIN_FILENO) ) {
            cout << input << endl;

        // fix EOF formatting if we *are* reading from a terminal
        } else if ( cin.eof() ) {
            cout << endl;
        }

        if ( input == "quit" ) break;

        try {
            result = ComputeExpression(input);
            cout << "Result: " << result << "\n" << endl;
        } catch ( const parse_error& err ) {
            cout << "Error: " << err.what() << "\n" << endl;
        }
    }

    cout << "Thanks for using our calculator!" << endl;

    return 0;             
}
