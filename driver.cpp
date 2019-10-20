#include "NotationConverter.hpp"

#include <iostream> 

using namespace std;

int main () {

    NotationConverter nc;

    //string output = nc.infixToPostfix("(((A + B) / (X +Y)) - R)");
    //string output1 = nc.infixToPrefix("(((A + B) / (X + Y)) - R)");
    //string output2 = nc.postfixToInfix("AB+");
    //string output3 = nc.prefixToInfix("[A + B]");
    //string output3 = nc.postfixToPrefix("X Y + A B + *");
    string output4 = nc.infixToPrefix("[A + B]");

    //cout << output << "test"<<endl; 
    //cout << output1 << "test"<< endl;
    //cout << output2 << "test"<< endl;
    //cout << output3 << "test"<< endl;
    //cout << output3 << "test"<< endl;
    cout << output4 << endl;




    return 0;
}