/*! \file */ 
/*! \brief main.cpp.
 *
 *  Starts the program.
*/
#include <iostream>
#include <string>

#include "RedBlackTree.h"

using namespace std;

//! Tree instance
RedBlackTree<int> myTree;

//! Functions prototypes
void return_to_menu();
void displayMainMenu();

/**
 * Get the user choice
*/
int getInput()
{
    int choice;
    cin >> choice;
    return choice;
}

/**
 * Insert itens in red-black tree
*/
void insertItem()
{
    /*! Variables to receive the commands parameter */
    int itemValue;

    do
    {
        /*! Check if all arguments was passed */
        cout << endl << "<<< New item value ('q' to return): ";

        if ( scanf("%i", &itemValue) == 1 )
        {
            //! Call the class insertion method
            myTree.insert(itemValue);
        }
    }
    while ( getchar() != 'q' );

    displayMainMenu();
}

/**
 * Search itens in red-black tree
*/
void searchtItem()
{
    /*! Variables to receive the commands parameter */
    int itemValue;
    int result = 0;

    do
    {
        /*! Check if all arguments was passed */
        cout << endl << "<<< Item to be searched ('q' to return): ";

        if ( scanf("%i", &itemValue) == 1 )
        {
            //! Call the class search method
            result = myTree.search(itemValue);

            //! Check the result
            if ( result != 0 )
            {
                cout << " [ Item found! ]";
            }
            else
            {
                cout << " [ Item not found! ]";
            }

            cout << endl;
        }
    }
    while ( getchar() != 'q' );

    displayMainMenu();
}

/**
 * Delete itens in red-black tree
*/
void deleteItem()
{
    /*! Variables to receive the commands parameter */
    int itemValue;

    do
    {
        /*! Check if all arguments was passed */
        cout << endl << "<<< Item to be deleted ('q' to return): ";

        if ( scanf("%i", &itemValue) == 1 )
        {
            //! Call the class insertion method
            //myTree.delete(itemValue);
        }
    }
    while ( getchar() != 'q' );

    displayMainMenu();
}

/**
 * Print the red-black tree
*/
void printTree()
{
    cout << endl << "================================================================" << endl;
    cout << "*** Red-Black Tree visualization" << endl;
    cout << "================================================================" << endl << endl;

    //! Print the updated tree
    myTree.print();

    cout << endl << "================================================================" << endl << endl;

    //! Check if the user wants to return to main menu
    return_to_menu();
}

/**
 * Handle the user input choice
*/
void inputHandler( int choice_ )
{
    switch( choice_ )
    {
        /*! Insert itens in red-black tree */
        case 1:
            insertItem();
            break;

        /*! Search item */
        case 2:
            searchtItem();
            break;

        /*! Remove item */
        case 3:
            deleteItem();
            break;

        /*! Print red-black tree */
        case 4:
            printTree();
            break;

        /*! Exit */
        case 5:
            exit(0);
            break;

        default:
            displayMainMenu();
            break;
    }
}

/**
 * Display the menu
*/
void displayMainMenu()
{
    system("clear");

    cout << endl << "================================================================" << endl;
    cout << "*** Red-Black Tree generator v0.25 ***" << endl;
    cout << "================================================================" << endl << endl;
    cout << "Please make your selection\n";
    cout << "1 - Insert itens in red-black tree\n";
    cout << "2 - Search item\n";
    cout << "3 - Remove item\n";
    cout << "4 - Print red-black tree\n";
    cout << "5 - Quit\n";
    cout << endl << "================================================================" << endl << endl;
    cout << "Choose an option: ";

    inputHandler(getInput());
}

/**
 * Function to return to menu
*/
void return_to_menu()
{
    char opt;
    cout << endl << "Would you like to return to main menu? (y or n): ";
    cin >> opt;

    if ( opt == 'y' || opt == 'Y' )
        displayMainMenu();
    else
        exit(0);
}

/********************************************//**
* Main
***********************************************/
int main( void )
{
    

    //! Display the application menu
    displayMainMenu();

    //! Status message
    cout << "<<< Finish with success! >>>" << endl << endl;

    /*! Main return */
    return 0;
}