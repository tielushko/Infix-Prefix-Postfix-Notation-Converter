#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H
#include "NotationConverterInterface.hpp"

#include <stack>

using std::stack; 

class NotationConverter: NotationConverterInterface
{
public:
    //NotationConverter();
    std::string postfixToInfix(std::string inStr); //below are overrides of the functions
    std::string postfixToPrefix(std::string inStr);

    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);

    std::string prefixToInfix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);

    //the function to check whether the character is an operator
    bool isOperator(char c) {
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^': 
                return true;
                break;
            default: 
                return false;
                break;
        }
    }

    //operation to check whether the character is an Operand A-Z a-z
    bool isOperand(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    
    /*
    int operationPriority (char c) {
        switch (c) {
            case '^': 
                return 3;
                break;
            case '/':
            case '*': 
                return 2;
                break;
            case '+':
            case '-':
                return 1;
                break;
            default:
                return 0;
                break;
        }
    }
    */
};
#endif
