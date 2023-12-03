/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * tests.cpp
 *   Automated Test Cases
 * 
 * Created:
 *   Jackson Yanek, Elijah Pijanowski, Mikaela Navarro
 *   01 December 2023
 *****/

#include <iostream>
#include "solver.hpp"
#include <iostream>
#include "solver.hpp"

// tests valid expressions -- makes sure that the result is the same as the expected result
void validTest(const std::string& input, double expectedResult, const std::string& testCase, double tolerance = 1e-6) {
    try {
        // parse the expression and compute
        double result = ComputeExpression(input);

        // verify if the result falls within the tolerance of the expected result
        if (std::abs(result - expectedResult) < tolerance) {
            std::cout << testCase << ": Passed " << "Result: " << result << std::endl;
        } else {
            // it result doesn't fall within tolerance, print a message and show results
            std::cout << testCase << ": Failed\n";
            std::cout << "  Expected: " << expectedResult << ", Actual: " << result << "\n";
        }
    } catch (const parse_error& err) {
        // if an exception occurs, print a message with the error
        std::cout << testCase << ": Failed\n";
        std::cout << "  Error: " << err.what() << "\n";
    }
}


// tests valid expressions -- makes sure that the result is the same as the expected result
void invalidTest(const std::string& input, const std::string& expectedError, const std::string& testCase) {
    try {
        // parse the expression and compute
        double result = ComputeExpression(input);

        // if parsing and computing pass, print a message
        std::cout << testCase << ": Failed\n";
        std::cout << "Expected failure, but got: " << result << "\n";
    } catch (const parse_error& err) {
        // if an exception occurs, check if message matches the expected error
        // if it matches, print 'Passed', else print a message and show results
        if (err.what() == expectedError) {
            std::cout << testCase << ": Passed " << "Error: " << err.what() << std::endl;
        } else {
            std::cout << testCase << " Expected Error: " << expectedError << ", Actual Error: " << err.what() << "\n";
        }
    }
}

// function that will run the following test cases
void runTests() {
    validTest("3 + 4", 7, "TC01");
    validTest("8 - (5 - 2)", 5, "TC02");
    validTest("10 * 2 / 5", 4, "TC03");
    validTest("2 ^ 3", 8, "TC04");
    validTest("4 * (3+2) % 7 - 1", 5, "TC05");
    validTest("(((2 + 3 ))) + (((1 + 2)))", 8, "TC06");
    validTest("((5 * 2) - ((3 / 1) + ((4 % 3))))", 6, "TC07");
    validTest("(((2 ^ (1 + 1)) + ((3 - 1) ^ 2)) / ((4 / 2) % 3))", 4, "TC08");
    validTest("(((((5 - 3))) * (((2 + 1))) + ((2 * 3))))", 12, "TC09");
    validTest("((9 + 6)) / ((3 * 1) / (((2 + 2))) - 1)", -60, "TC10");
    validTest("+(-2) * (-3) - ((-4) / (+5))", 6.8, "TC11");
    validTest("-(+1) + (+2)", 1, "TC12");
    validTest("-(-(-3)) + (-4) + (+5)", -2, "TC13");
    validTest("+2 ^ (-3)", 0.125, "TC14");
    validTest("-(+2) * (+3) - (-4) / (-5)", -6.8, "TC15");

    invalidTest("2 * (4 + 3 - 1", "Unbalanced Brackets", "TC16");
    invalidTest("* 5 + 2", "Missing Operands", "TC17");
    invalidTest("4 / 0", "Undefined Operation: Division by Zero", "TC18");
    invalidTest("5 (2 + 3)", "Missing Operators", "TC19");
    invalidTest("7 & 3", "Invalid Character in Expression", "TC20");
    invalidTest("(((3 + 4) - 2) + (1)", "Unbalanced Brackets", "TC21");
    invalidTest("((5 + 2) / (3 * 0))", "Undefined Operation: Division by Zero", "TC22");
    invalidTest("((2 -) 1 + 3)", "Missing Operands", "TC23");
    invalidTest("((4 * 2) + ( - ))", "Missing Operands", "TC24");
    invalidTest("((7 * 3) @ 2)", "Invalid Character in Expression", "TC25");

    validTest("3.14 + 2.5", 5.64, "TC26");

    // testing large numbers, testing is done similarly as above
    double base_TC27 = 1000000;
    double exponent_TC27 = 2;
    double expected_result_TC27 = std::pow(base_TC27, exponent_TC27);
    std::string input_TC27 = "1000000 ^ 2";

    try {
        double result_TC27 = ComputeExpression(input_TC27);
        if (result_TC27 == expected_result_TC27) {
            std::cout << "TC27: Passed " << "Result: " << result_TC27 << std::endl;
        } else {
            std::cout << "TC27: Failed\n";
            std::cout << "  Expected: " << expected_result_TC27 << ", Actual: " << result_TC27 << "\n";
        }
    } catch (const parse_error& err) {
        std::cout << "TC27: Failed\n";
        std::cout << "  Error: " << err.what() << "\n";
    }

    validTest("2e3 + 4e-2", 2000.04, "TC28");

    invalidTest("10e", "Invalid Numeric Constant: scientific notation invalid exponent", "TC29");
    invalidTest("3e^2 + 4e-3", "Invalid Numeric Constant: scientific notation invalid exponent", "TC30");

    validTest("10.3e2", 1030, "TC31");

    invalidTest("6e2.5", "Invalid Numeric Constant: scientific notation invalid exponent", "TC32");

    validTest("3 * (4 + [5 - 2]) / (7 * [2 + 1])", 1, "TC33");
}
