// main.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): put your existing implementation of main here
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI
    my_string operate;
    my_string first;
    my_string second;

    /*
    while (true) {
        cout << ">> ";

        cin >> first;
        if (first == "quit" || first == "q") {
            cout << "farvel!" << endl;
            break;
        }

        cin >> operate >> second;

        if (operate == "+") {
            cout << "ans = " << endl << endl << "    " << add(first, second) << endl;
        } else if (operate == "-") {
            cout << "ans = " << endl << endl << "    " << subtract(first, second) << endl;
        } else if (operate == "*") {
            cout << "ans = " << endl << endl << "    " << multiply(first, second) << endl;
        } 
        cout << endl;
    }
    */

    return 0;
}
