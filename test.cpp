#include <iostream>
#include <string>

using namespace std;
int main () {


    string four = "4";
    string twelve = "12";

    if (four < twelve) {
        cout << "4, 12";
    } else if (twelve < four) {
        cout << "12, 4";
    }
    return 0;
}