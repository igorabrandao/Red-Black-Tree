/*! \file */ 
/*! \brief main.cpp.
 *
 *  Starts the program.
*/
#include <iostream>
#include <string>

#include "RedBlackTree.h"

using namespace std;

/********************************************//**
* Main
***********************************************/
int main( void )
{
    RedBlackTree<int> myTree; //declare our tree
    int value = 1; // value to hold user input for insertion

    cout << "Welcome... End this program by inputing a -99 sentinel value" << endl << endl;

    while ( value != -99 ) // loop ends with a sentinel value of -99
    {
        cout << "Please enter a value" << endl;
        cin >> value; // input the value
        myTree.insert(value); // insert the value into the tree
        myTree.print(); // print the tree
    }

    return 0;
}