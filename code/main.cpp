/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * main.c
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
 *   19 September 2023
 *****/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::getline;

#include <string>
using std::string;

#include <exception>
using std::invalid_argument;

#include <unistd.h>
// using isatty;

#include "solver.hpp"

int main() {
    // first line is empty to look pretty
    cout << "                                                  \n"
         << "              ==== TEAM ORANGE ====               \n"
         << "                Expression Solver                 \n"
         << "              ====    =====    ====               \n"
         << "                                                  \n"
         << "Please enter equations using only these operators:\n"
         << " - addition (+)                                   \n"
         << " - subtraction (-)                                \n"
         << " - multiplication (*)                             \n"
         << " - division (/)                                   \n"
         << " - exponentiation (^ or **)                       \n"
         << "                                                  \n"
         << "Parentheses and unary (+) and (-) are supported!  \n"
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

        try {
            result = ComputeExpression(input);
            cout << "Result: " << result << "\n" << endl;
        } catch ( const invalid_argument& err ) {
            cout << "Error: " << err.what() << "\n" << endl;
        }
    }

    cout << "Thanks for using our calculator!" << endl;

    return 0;             
}