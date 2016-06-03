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
    //! Tree instance
    RedBlackTree<int> myTree;

    //! Auxiliary variable
    int input_value = 1;

    cout << endl << "================================================================" << endl;
    cout << "*** Gerador de arvore rubro-negra v0.1 ***" << endl;
    cout << "================================================================" << endl << endl;

    // Loops ends with value of -999
    while ( input_value != -999 )
    {
        //! User input
        cout << endl << "Informe um valor a ser inserido [-999 para finalizar]: ";
        cin >> input_value;
        cout << endl;

        //! Call the class insertion method
        myTree.insert(input_value);

        //! Print the updated tree
        myTree.print();
    }

    /*! Main return */
    return 0;
}