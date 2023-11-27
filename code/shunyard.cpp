#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <cmath>

using namespace std;
stack <string> opStack;
queue <string> numStack;
map <char, int> opMap = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};

int math(int a, int b, char op){
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
    }
}

void shunyard(const string& input){
    for (int i = 0; i < input.size(); i++){
        if (isspace(input[i])){
            continue;
        }
        else if (input[i] == '('){
            opStack.push("(");
        }
        else if (input[i] == ')'){
            while (opStack.top() != "("){
                numStack.push(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
        else if (isdigit(input[i])){
            string num;
            while (isdigit(input[i])){
                num += input[i];
                input[i] = input[++i];
            }
            numStack.push(num);
            i--;
        }
        else if (opMap.count(input[i])){
            while (!opStack.empty() && opMap[opStack.top()] >= opMap[input[i]]){
                numStack.push(opStack.top());
                opStack.pop();
            }
            opStack.push(input[i]);
        }
        
    }
    while (!opStack.empty()){
        numStack.push(opStack.top());
        opStack.pop();
    
}
}

int main(){
    string input;
    getline(cin, input);
    shunyard(input);
    while (!numStack.empty()){
        cout << numStack.front() << " ";
        numStack.pop();
    }
    cout << endl;
    return 0;
}




    
