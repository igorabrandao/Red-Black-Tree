/*!
    <PRE>
        SOURCE FILE : RedBlackTree.h
        DESCRIPTION.: Red Black Tree class - with implementation.
        AUTHORS.....: Igor A. Brandão
        CONTRIBUTORS: Igor A. Brandão
        LOCATION....: IMD/UFRN.
        SATARTED ON.: MAY/2016
        CHANGES.....: Structure and functions implemented.

        TO COMPILE..: Use makefile.
        OBS.........: Part of the EDB2 Project.

        LAST UPDATE.: May 29th, 2016.
        LAST UPDATE.: May 30th, 2016.
        LAST UPDATE.: May 31st, 2016.
        LAST UPDATE.: Jun  1st, 2016.
        LAST UPDATE.: Jun  2nd, 2016.
        LAST UPDATE.: Jun  3th, 2016.
    </PRE>
*/

#ifndef RedBlackTree_H_
#define RedBlackTree_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace std;

// ***********************OPERATIONS************************
// RBTreeNode( )        --> Class constructor
// *********************************************************

/*! Class prototype */
template <class Comparable>
class RedBlackTree;

/*! The node is a class with a constructor and overloads '<' operator */
template <class Comparable>
class RBTreeNode
{
    /*! Enum to define the node color */
    enum NodeColor {Red, Black};

    /*! Basic members */
    Comparable  value;
    RBTreeNode  *lChildPtr;
    RBTreeNode  *rChildPtr;
    NodeColor   color;

    /*! Node constructor */
    RBTreeNode( Comparable v = Comparable(), RBTreeNode *l = NULL, RBTreeNode *r = NULL, NodeColor c = Black )
        : value(v), color(c), lChildPtr(l), rChildPtr(r) //!< initialize the basic members
    {
        /*! empty */
    }

    friend class RedBlackTree<Comparable>;
};

// ******************PUBLIC OPERATIONS*********************
// RedBlackTree( void )                             --> Class constructor
// RedBlackTree( const RedBlackTree<Comparable>& )  --> Copy constructor
// const RedBlackTree<Comparable>& operator         --> Assignment operator
// ~RedBlackTree()                                  --> Class destructor
// insert( Comparable newItem )                     --> Insertion function
// void print( void ) const                         --> Print function

// ***********************ERRORS****************************
// std::bad_alloc thrown if needed.

/*! The red black tree class itself */
template <class Comparable>
class RedBlackTree
{
    /*!
     * Public section
    */
    public:

        /*! Class constructor to create an empty red-black tree */
        RedBlackTree( void );

        /*! Copy constructor (deep copy) */
        RedBlackTree( const RedBlackTree<Comparable>& old );

        /*! Assignment operator */
        const RedBlackTree<Comparable>& operator = ( const RedBlackTree<Comparable>& rhs );

        /*! Class destructor to release memory */
        ~RedBlackTree();

        /*! Red-black tree's insertion function. Could throws a bad_alloc exception if no enough space */
        void insert( Comparable newItem );

        /*! Print all the tree's nodes */
        void print( void ) const;

    /*!
     * Private section
    */
    private:

        /*! Swaps the node color (applied in the split method) */
        void swapColor( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr, RBTreeNode<Comparable>*& grandPtr );

        /*! Perform a right rotation
         *  rotate the nodePtr around its left child
         *  parentPtr points to the parent of nodePtr
        */
        void rightRotate( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr );

        /*! Perform a left rotation
         *  rotate the nodePtr around its right child
         *  parentPtr points to the parent of nodePtr 
        */
        void leftRotate( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr );

        /*! split a 4-node: nodePtr
         *  parentPtr points to the parent of nodePtr
         *  grandPtr points to the parent of parentPtr
         *  greatPtr points to the parent of grandPtr
        */
        void split( RBTreeNode<Comparable>* nodePtr, RBTreeNode<Comparable>* parentPtr, RBTreeNode<Comparable>* grandPtr,
                     RBTreeNode<Comparable>* greatPtr );

        /*! Clone constructor (deep copy) */
        RBTreeNode<Comparable> * clone( RBTreeNode<Comparable> * nodePtr ) const;

        /*! release memory of the tree, but don't release pseudo root and theLeaf */
        void reclaimMemory( RBTreeNode<Comparable> *nodePtr ) const;

        /*! Print the tree rooted at nodePtr
         *  The parameter level specifies the level of the nodePtr in the tree.
         *  You need to use this parameter to adjust indentation.
        */
        void print( RBTreeNode<Comparable> *nodePtr, int level ) const;

    /*!
     * Private section
    */
    private:

            /*! Basic members */
            RBTreeNode<Comparable>* theLeaf;    //!< actual leaf node
            RBTreeNode<Comparable>* m_root;     //!< pointer to pseudo root
            RBTreeNode<Comparable>* nullNode;
};

#include "RedBlackTree.cpp"
#endif // RedBlackTree_H

/* --------------------- [ End of the RedBlackTree.h header ] ------------------- */
/* ============================================================================== */