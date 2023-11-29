/*****
 * TEAM ORANGE
 * 
 * EECS 348 Expression Solver Project
 * shunyard.cpp
 *   Implementation of Djikstra's Shunting Yard algorithm to reorganize the
 *   infix-formatted input token stream into a postfix (aka Reverse Polish Notation)
 *   output token stream
 * 
 * Created:
 *   Mahgoub Husien
 *   27 November 2023
 * 
 * Last Edited:
 *   Adam Albee (2888458)
 *   29 November 2023
 *****/


#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <cmath>

using namespace std;
stack <char> opStack;
stringstream print;
map <char, int> opMap = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

float math(float a, float b, char op){
    switch (op){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}

void shunyard(const string& input){
    for (int i = 0; i < input.size(); i++){
        if (isspace(input[i])){
            continue;
        }
        if (isdigit(input[i]) || input[i] == '.'){
            print << input[i];
        }
        else if (input[i] == '('){
            opStack.push('(');
        }
        else if (input[i] == ')'){
            while (!opStack.empty() && opStack.top() != '('){
                print << opStack.top();
                opStack.pop();
            }
            opStack.pop();
        }
        else if (opMap.count(input[i])){
            print << ' ';
            while (!opStack.empty() && opStack.top() != '(' && opMap[opStack.top()] >= opMap[input[i]]){
                print << opStack.top();
                opStack.pop();
            }
            opStack.push(input[i]);
        }
        
    }
    while (!opStack.empty()){
        print << ' ' << opStack.top();
        opStack.pop();
    }

}

float calculate(const string& input){
    stack <float> solve;
    float num1, num2;
    for (int i = 0; i < input.size(); i++){
        if (isspace(input[i])){
            continue;
        }
        if (isdigit(input[i]) || input[i] == '.'){
            float num = 0;
            while (isdigit(input[i]) || input[i] == '.'){
                num = num * 10 + input[i] - '0';
                i++;
            }
            i--;
            solve.push(num);
        }
        else if (opMap.count(input[i])){
            num2 = solve.top();
            solve.pop();
            num1 = solve.top();
            solve.pop();
            solve.push(math(num1, num2, input[i]));
        }
    }
    return solve.top();
}

int main(){
    string input = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    shunyard(input);
    cout << print.str() << endl;
    cout << calculate(print.str()) << endl;
    return 0;
}
