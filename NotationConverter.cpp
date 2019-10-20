#include "NotationConverter.hpp"
#include <iostream> 
#include <algorithm>

using namespace std;

std::string NotationConverter::postfixToInfix(std::string inStr) {
    int len = inStr.size(); // get the length of the string
    stack<string> operationStack; 
    string converted = ""; 
    string op1, op2;

    //check the notation correctness
    if (!isOperand(inStr[0])) {
        throw std::runtime_error("Incorrect Notation!");
        //cout << "Incorrect notation!";
        return ""; 
    }

    for (int i = 0; i < len; i++) { //iterate through string
        if (isOperand(inStr[i])) { //if an operand
            string toPush(1, inStr[i]);
            operationStack.push(toPush); //push to stack 
        } else if (isOperator(inStr[i])) { // if an operator
            op2 = operationStack.top();  //remove the top 2 operators from stack and add them back as a single string in proper notation
            operationStack.pop();
            op1 = operationStack.top(); 
            operationStack.pop();
            operationStack.push("(" + op1 + ' ' + inStr[i] + ' ' + op2 + ")");   
        } else if(inStr[i] == ' ') { //allows to omit the empty spaces
            continue;
        } else { //in case any other fail, then must have used wrong symbols.
            throw std::runtime_error("Using incorrect operator or operand");
            return "";
        }
    }
    converted = operationStack.top(); //final infix
    operationStack.pop(); //cleaning up
    return converted;
}

std::string NotationConverter::postfixToPrefix(std::string inStr){
    string converted; 
    converted = postfixToInfix(inStr);  //simple steps using other functions
    converted = infixToPrefix(converted);

    return converted;
}

std::string NotationConverter::infixToPostfix(std::string inStr){

    int len = inStr.size(); 
    stack<char> operationStack;
    string converted = "";

    //error check for proper notation
    if (inStr[0] != '(') {
            throw std::runtime_error("Incorrect notation!");
            //cout << "Incorrect notation!";
            return "";
    }

    //iterate through each character in string    
    for (int i = 0; i < len; i++) {
        if (isOperand(inStr[i])) {
            converted += inStr[i]; //push to output if an operand
        } else if (inStr[i] == '(') { //push to stack
            operationStack.push(inStr[i]);
        } else if (inStr[i] == ')') { // remove operands and operations from stack until reach (
            while(operationStack.top() != '(') {
                char temp = operationStack.top();
                operationStack.pop();
                converted += temp;
            }
            operationStack.pop(); 
        } else if (isOperator(inStr[i])) { 
            operationStack.push(inStr[i]);
        } else if(inStr[i] == ' ') { //if space, ignore and continue
            continue;
        } else { //in case wrong characters
            throw std::runtime_error("Using incorrect operator or operand");
            //cout << "Using incorrect operator or operand"; 
            return "";
        }
    }

    string returned = "";

    //this code block helps me add spaces and remove the last space to return the output string. 
    for (auto i = 0; i < converted.size(); i++) {
        returned += converted[i];
        returned += ' ';
    }
    string copy; 

    for (auto i = 0; i < returned.size() - 1; i++) {
        copy += returned[i];
    }

    return copy;
}

std::string NotationConverter::infixToPrefix(std::string inStr){
    int len = inStr.size();
    string converted = "";

    //prefix and postfix are similar so i reverse the initial string
    reverse(inStr.begin(), inStr.end());

    //replace the ( with ) and ) with (
    for (int i = 0; i < len; i++) {
        if (inStr[i] == '(')
            inStr[i] = ')';
        else if (inStr[i] == ')') 
            inStr[i] = '(';
    }

    //convert to postfix
    converted = infixToPostfix(inStr); 

    //reverse the conversion to get prefix
    reverse(converted.begin(), converted.end());

    return converted;
}

std::string NotationConverter::prefixToInfix(std::string inStr) {
    int len = inStr.size(); 
    stack<string> operationStack;

    //check for wrong notation
    if (!isOperator(inStr[0])) {
        throw std::runtime_error("Incorrect prefix expression!");
        //cout << "Incorrect prefix expression!";
        return "";
    }

    //similar process where we reverse, then convert to postfix, then reverse again to get prefix
    reverse(inStr.begin(), inStr.end());
    string converted = postfixToInfix(inStr); 
    reverse(converted.begin(), converted.end()); 

    //don't forget to replace the characters. 
    for (int i = 0; i < converted.size(); i++) {
        if (converted[i] == '(')
            converted[i] = ')';
        else if (converted[i] == ')') 
            converted[i] = '(';
    }

    return converted; 
}

std::string NotationConverter::prefixToPostfix(std::string inStr){
    //really simple function if you have the middle steps executed correctly.
    string converted; 
    converted = prefixToInfix(inStr);
    string newString; 
    newString = infixToPostfix(converted);

    return newString;
}
